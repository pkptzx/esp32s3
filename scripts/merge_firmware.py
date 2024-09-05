Import('env')
import os

OUTPUT_DIR = "$BUILD_DIR{}".format(os.path.sep)
APP_BIN = "$BUILD_DIR/${PROGNAME}.bin"


def copy_merge_bins(source, target, env):
    print("========= [merge-firmware] ==========")
    firmware_src = str(target[0])
    flash_images = env.Flatten(env.get("FLASH_EXTRA_IMAGES", [])) + ["$ESP32_APP_OFFSET", APP_BIN]
    name = firmware_src.split(os.path.sep)[2]
    flash_size = env.GetProjectOption("board_upload.flash_size")
    board = env.BoardConfig()
    f_flash = board.get("build.f_flash", "40000000L")
    flash_mode = board.get("build.flash_mode", "dio")
    memory_type = board.get("build.arduino.memory_type", "qio_qspi")
    if flash_mode == "qio" or flash_mode == "qout":
        flash_mode = "dio"
    if memory_type == "opi_opi" or memory_type == "opi_qspi":
        flash_mode = "dout"
    flash_freq = '40m'
    if (f_flash == '80000000L'):
        flash_freq = '80m'
    mcu = board.get("build.mcu", "esp32")
    firmware_dst = "{}{}_{}_{}_0x0.bin".format(OUTPUT_DIR, mcu, name, flash_size)
    if os.path.isfile(firmware_dst):
        os.remove(firmware_dst)
    cmd = " ".join(
        ["$PYTHONEXE", "$OBJCOPY", '--chip', mcu, 'merge_bin', '--output', firmware_dst, '--flash_mode', flash_mode,
         '--flash_size', flash_size, '--flash_freq', flash_freq] + flash_images)
    env.Execute(cmd)    


env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", [copy_merge_bins])