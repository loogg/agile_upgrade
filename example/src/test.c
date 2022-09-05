#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <agile_upgrade.h>

extern const struct agile_upgrade_ops agile_upgrade_file_ops;

int main(int argc, char *argv[]) {
    if (argc < 2) return -1;

    agile_upgrade_t src_agu = {0};
    src_agu.name = "src";
    src_agu.user_data = argv[1];
    src_agu.ops = &agile_upgrade_file_ops;

    agile_upgrade_t dst_agu = {0};
    dst_agu.name = "dst";
    dst_agu.user_data = "./upgrade.bin";
    dst_agu.ops = &agile_upgrade_file_ops;

    agile_upgrade_release(&src_agu, &dst_agu, 0);

    return 0;
}
