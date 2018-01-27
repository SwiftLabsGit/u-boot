/*
 * Copyright (C) 2018 Swift Labs Inc.
 *
 * Configuration settings for the Swiftcore V1 Board
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __MX6UL_SWIFTCORE_V1_CONFIG_H
#define __MX6UL_SWIFTCORE_V1_CONFIG_H

#include <asm/arch/imx-regs.h>
#include <linux/sizes.h>
#include "mx6_common.h"
#include <asm/mach-imx/gpio.h>

/* SPL options */
#include "imx6_spl.h"

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART2_BASE

/* MMC Configs */
#ifdef CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	USDHC2_BASE_ADDR

/* NAND pin conflicts with usdhc2 */
#ifdef CONFIG_NAND_MXS
#define CONFIG_SYS_FSL_USDHC_NUM	1
#else
#define CONFIG_SYS_FSL_USDHC_NUM	2
#endif

#endif

/* I2C configs */
#ifdef CONFIG_CMD_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
#define CONFIG_SYS_I2C_MXC_I2C2		/* enable I2C bus 2 */
#define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */
#define CONFIG_SYS_I2C_SPEED		100000
#endif

#define CONFIG_SYS_MMC_IMG_LOAD_PART	1

#define CONFIG_EXTRA_ENV_SETTINGS \
  "username=dan\0" \
  "set_paths= run clear_paths; setenv bootfile ${username}/${bootfile}; setenv fdt_file ${username}/${fdt_file}; setenv nfsroot /nfs/${username}/rootfs;\0" \
  "clear_paths= setenv bootfile zImage; setenv fdt_file imx6ul-swiftcore-v1-evk.dtb;\0" \
  "ethact=asx0\0" \
  "serverip=192.168.0.199\0" \
  "powercmd=i2c dev 2; i2c mw 0x08 0x70 0x10\0" \
  "autoload=no\0" \
  "bootfile=zImage\0" \
  "fdt_file=imx6ul-swiftcore-v1-evk.dtb\0" \
  "nfsroot=/nfs/rootfs\0" \
  "script=boot.scr\0" \
  "image=zImage\0" \
  "console=ttymxc1\0" \
  "fdt_high=0xffffffff\0" \
  "initrd_high=0xffffffff\0" \
  "fdt_addr=0x83000000\0" \
  "boot_fdt=try\0" \
  "ip_dyn=yes\0" \
  "mmcdev="__stringify(CONFIG_SYS_MMC_ENV_DEV)"\0" \
  "mmcpart=" __stringify(CONFIG_SYS_MMC_IMG_LOAD_PART) "\0" \
  "mmcroot=" CONFIG_MMCROOT " rootwait rw\0" \
  "mmcautodetect=yes\0" \
  "mmcargs=setenv bootargs console=${console},${baudrate} " \
    "root=${mmcroot}\0" \
  "loadbootscript=" \
    "fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0" \
  "bootscript=echo Running bootscript from mmc ...; " \
    "source\0" \
  "loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
  "loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
  "nfsboot=run netargs; bootz $loadaddr - $fdt_addr\0" \
  "sdboot=echo Booting from mmc ...; mmc dev ${mmcdev}; "\
    "if mmc rescan; then "\
      "if run loadimage; then "\
        "run mmcboot; "\
      "else "\
        "echo ERROR: Cannot run loadimage; "\
      "fi; "\
    "else "\
      "echo ERROR: Cannot run mmc rescan; "\
    "fi;\0"\
  "mmcboot=echo Booting from mmc ...; " \
    "run mmcargs; " \
    "if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
      "if run loadfdt; then " \
        "bootz ${loadaddr} - ${fdt_addr}; " \
      "else " \
        "if test ${boot_fdt} = try; then " \
          "bootz; " \
        "else " \
          "echo WARN: Cannot load the DT; " \
        "fi; " \
      "fi; " \
    "else " \
      "bootz; " \
    "fi;\0" \
  "netargs=setenv bootargs console=${console},${baudrate} " \
    "rw " \
    "root=/dev/mmcblk1p2 " \
    "ip=dhcp " \
    "nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
  "netargs=setenv bootargs console=${console},${baudrate} " \
    "root=/dev/nfs " \
  "ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" \

#define CONFIG_BOOTCOMMAND \
  "echo Configuring PMIC...; run powercmd; "\
  "echo Configuring file paths for username: $username; "\
  "run set_paths; "\
  "echo Booting from network ...; usb start; setenv ethact asx0; "\
  "if dhcp && tftp $loadaddr $bootfile && tftp $fdt_addr $fdt_file; "\
    "then run nfsboot; "\
  "else "\
    "echo WARN: Issue with TFTP.; "\
    "run clear_paths; "\
    "run sdboot; "\
  "fi;"

/* Miscellaneous configurable options */
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x8000000)

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ			1000

#define CONFIG_CMDLINE_EDITING

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* environment organization */
#define CONFIG_ENV_SIZE			SZ_8K
#define CONFIG_ENV_OFFSET		(8 * SZ_64K)
#define CONFIG_SYS_MMC_ENV_DEV		1   /* USDHC2 */
#define CONFIG_SYS_MMC_ENV_PART		0	/* user area */
#define CONFIG_MMCROOT			"/dev/mmcblk1p2"  /* USDHC2 */

#ifndef CONFIG_SYS_DCACHE_OFF
#endif

#ifdef CONFIG_FSL_QSPI
#define CONFIG_SF_DEFAULT_BUS		0
#define CONFIG_SF_DEFAULT_CS		0
#define CONFIG_SF_DEFAULT_SPEED	40000000
#define CONFIG_SF_DEFAULT_MODE		SPI_MODE_0
#define FSL_QSPI_FLASH_NUM		1
#define FSL_QSPI_FLASH_SIZE		SZ_32M
#endif

/* USB Configs */
#ifdef CONFIG_CMD_USB
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_MXC_USB_PORTSC  (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS   0
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#endif

#ifdef CONFIG_CMD_NET
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define CONFIG_FEC_ENET_DEV		0

#if (CONFIG_FEC_ENET_DEV == 0)
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR          0x2
#define CONFIG_FEC_XCV_TYPE             RMII
#elif (CONFIG_FEC_ENET_DEV == 1)
#define IMX_FEC_BASE			ENET2_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR		0x1
#define CONFIG_FEC_XCV_TYPE		RMII
#endif
#define CONFIG_ETHPRIME			"FEC"
#endif

#define CONFIG_IMX_THERMAL

#ifndef CONFIG_SPL_BUILD
#ifdef CONFIG_VIDEO
#define CONFIG_VIDEO_MXS
#define CONFIG_VIDEO_LOGO
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_VIDEO_BMP_LOGO
#define MXS_LCDIF_BASE MX6UL_LCDIF1_BASE_ADDR
#endif
#endif

#endif
