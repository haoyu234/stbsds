#define STB_HAS_SDS
#define STB_DS_IMPLEMENTATION
#define STB_SPRINTF_IMPLEMENTATION

#include <stdarg.h>
#include <stdint.h>

#include <sds.h>
#include <stb_ds.h>
#include <stb_sprintf.h>

struct sprintfcb_ctx {
  sds res;
  struct {
    uint32_t preallocated : 1;
  } ops;
  char buf[STB_SPRINTF_MIN];
};

static char *sprintf_cb(const char *buf, void *user, int len) {
  struct sprintfcb_ctx *ctx = user;

  if (ctx->ops.preallocated) {
    sdsIncrLen(ctx->res, len);
  } else {
    ctx->res = sdscatlen(ctx->res, buf, len);
    if (!ctx->res) {
      return NULL;
    }
  }

  if (len < STB_SPRINTF_MIN) {
    ctx->ops.preallocated = 0;
    return ctx->buf;
  }

  int offset = sdslen(ctx->res);
  ctx->res = sdsMakeRoomFor(ctx->res, STB_SPRINTF_MIN);

  if (!ctx->res) {
    return NULL;
  }

  ctx->ops.preallocated = 1;
  return &ctx->res[offset];
}

sds sdsstbcatvprintf(sds s, const char *fmt, va_list va) {
  struct sprintfcb_ctx ctx = {
      .res = s,
  };

  if (ctx.res) {
    stbsp_vsprintfcb(sprintf_cb, &ctx, ctx.buf, fmt, va);
  }

  return ctx.res;
}

sds sdsstbcatprintf(sds s, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  sds res = sdsstbcatvprintf(s, fmt, ap);
  va_end(ap);
  return res;
}
