#include <gtest/gtest.h>
#include <sds.h>
#include <stbsds.h>

TEST(sprintf, S) {
  sds s = sdsempty();
  sds s2 = sdsnewlen("123", 3);
  s = sdsstbcatprintf(s, "-%S-", s2);

  EXPECT_EQ(sdslen(s), 5);
  EXPECT_EQ(s[0], '-');
  EXPECT_EQ(s[1], '1');
  EXPECT_EQ(s[2], '2');
  EXPECT_EQ(s[3], '3');
  EXPECT_EQ(s[4], '-');

  sdsfree(s);
  sdsfree(s2);
}
