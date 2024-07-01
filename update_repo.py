import subprocess
import tempfile
import shutil
import os
import re
import glob

INCLUDE_DIR = "include"
SOURCE_DIR = "src"

STB_REPO_URL = "https://github.com/nothings/stb.git"
STB_SOURCE = {
    "stb_ds.h": INCLUDE_DIR,
    "stb_sprintf.h": INCLUDE_DIR,
}

SDS_REPO_URL = "https://github.com/jcorporation/sds.git"
SDS_SOURCE = {
    "sds.h": INCLUDE_DIR,
    "sdsalloc.h": INCLUDE_DIR,
    "sds.c": SOURCE_DIR,
}


def copy_source(source_dir: str, target_dir_dict: dict[str, str]):
    for name, target_dir in target_dir_dict.items():
        src = os.path.join(source_dir, name)
        dst = os.path.join(target_dir, name)
        shutil.copyfile(src, dst)


def clone_temp(repo_url: str) -> str:
    path = tempfile.mkdtemp()
    subprocess.check_call(
        ["git", "clone", "--depth", "1", repo_url, path],
    )
    return path


def get_project_name(clone_url: str) -> str:
    idx = clone_url.rfind("/")
    name = clone_url[idx + 1 :]

    if "." in name:
        idx = name.find(".")
        return name[:idx]
    return name


def update_repo(clone_url: str, target_dir_dict: dict[str, str]):
    name = get_project_name(clone_url)

    clone_dir = clone_temp(clone_url)
    copy_source(clone_dir, target_dir_dict)

    src = os.path.join(clone_dir, "LICENSE")
    dst = os.path.join(SOURCE_DIR, f"{name}.LICENSE")
    shutil.copyfile(src, dst)


def apply_patchs():
    patchs = glob.glob("patchs/*.patch")
    subprocess.check_call(
        [
            "git",
            "apply",
            *patchs,
        ],
    )


def main():
    update_repo(STB_REPO_URL, STB_SOURCE)
    update_repo(SDS_REPO_URL, SDS_SOURCE)
    apply_patchs()


if __name__ == "__main__":
    main()
