<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file describes the काष्ठाure passed from the BootX application
 * (क्रम MacOS) when it is used to boot Linux.
 *
 * Written by Benjamin Herrenschmidt.
 */


#अगर_अघोषित _UAPI__ASM_BOOTX_H__
#घोषणा _UAPI__ASM_BOOTX_H__

#समावेश <linux/types.h>

#अगर_घोषित macपूर्णांकosh
#समावेश <Types.h>
#समावेश "linux_type_defs.h"
#पूर्ण_अगर

#अगर_घोषित macपूर्णांकosh
/* All this requires PowerPC alignment */
#आशय options align=घातer
#पूर्ण_अगर

/* On kernel entry:
 *
 * r3 = 0x426f6f58    ('BooX')
 * r4 = poपूर्णांकer to boot_infos
 * r5 = शून्य
 *
 * Data and inकाष्ठाion translation disabled, पूर्णांकerrupts
 * disabled, kernel loaded at physical 0x00000000 on PCI
 * machines (will be dअगरferent on NuBus).
 */

#घोषणा BOOT_INFO_VERSION               5
#घोषणा BOOT_INFO_COMPATIBLE_VERSION    1

/* Bit in the architecture flag mask. More to be defined in
   future versions. Note that either BOOT_ARCH_PCI or
   BOOT_ARCH_NUBUS is set. The other BOOT_ARCH_NUBUS_xxx are
   set additionally when BOOT_ARCH_NUBUS is set.
 */
#घोषणा BOOT_ARCH_PCI                   0x00000001UL
#घोषणा BOOT_ARCH_NUBUS                 0x00000002UL
#घोषणा BOOT_ARCH_NUBUS_PDM             0x00000010UL
#घोषणा BOOT_ARCH_NUBUS_PERFORMA        0x00000020UL
#घोषणा BOOT_ARCH_NUBUS_POWERBOOK       0x00000040UL

/*  Maximum number of ranges in phys memory map */
#घोषणा MAX_MEM_MAP_SIZE				26

/* This is the क्रमmat of an element in the physical memory map. Note that
   the map is optional and current BootX will only build it क्रम pre-PCI
   machines */
प्रकार काष्ठा boot_info_map_entry
अणु
    __u32       physAddr;                /* Physical starting address */
    __u32       size;                    /* Size in bytes */
पूर्ण boot_info_map_entry_t;


/* Here are the boot inक्रमmations that are passed to the bootstrap
 * Note that the kernel arguments and the device tree are appended
 * at the end of this काष्ठाure. */
प्रकार काष्ठा boot_infos
अणु
    /* Version of this काष्ठाure */
    __u32       version;
    /* backward compatible करोwn to version: */
    __u32       compatible_version;

    /* NEW (vers. 2) this holds the current _logical_ base addr of
       the frame buffer (क्रम use by early boot message) */
    __u8*       logicalDisplayBase;

    /* NEW (vers. 4) Apple's machine identअगरication */
    __u32       machineID;

    /* NEW (vers. 4) Detected hw architecture */
    __u32       architecture;

    /* The device tree (पूर्णांकernal addresses relative to the beginning of the tree,
     * device tree offset relative to the beginning of this काष्ठाure).
     * On pre-PCI macपूर्णांकosh (BOOT_ARCH_PCI bit set to 0 in architecture), this
     * field is 0.
     */
    __u32       deviceTreeOffset;        /* Device tree offset */
    __u32       deviceTreeSize;          /* Size of the device tree */

    /* Some infos about the current MacOS display */
    __u32       dispDeviceRect[4];       /* left,top,right,bottom */
    __u32       dispDeviceDepth;         /* (8, 16 or 32) */
    __u8*       dispDeviceBase;          /* base address (physical) */
    __u32       dispDeviceRowBytes;      /* rowbytes (in bytes) */
    __u32       dispDeviceColorsOffset;  /* Colormap (8 bits only) or 0 (*) */
    /* Optional offset in the registry to the current
     * MacOS display. (Can be 0 when not detected) */
     __u32      dispDeviceRegEntryOffset;

    /* Optional poपूर्णांकer to boot ramdisk (offset from this काष्ठाure) */
    __u32       ramDisk;
    __u32       ramDiskSize;             /* size of ramdisk image */

    /* Kernel command line arguments (offset from this काष्ठाure) */
    __u32       kernelParamsOffset;

    /* ALL BELOW NEW (vers. 4) */

    /* This defines the physical memory. Valid with BOOT_ARCH_NUBUS flag
       (non-PCI) only. On PCI, memory is contiguous and it's size is in the
       device-tree. */
    boot_info_map_entry_t
    	        physMemoryMap[MAX_MEM_MAP_SIZE]; /* Where the phys memory is */
    __u32       physMemoryMapSize;               /* How many entries in map */


    /* The framebuffer size (optional, currently 0) */
    __u32       frameBufferSize;         /* Represents a max size, can be 0. */

    /* NEW (vers. 5) */

    /* Total params size (args + colormap + device tree + ramdisk) */
    __u32       totalParamsSize;

पूर्ण boot_infos_t;


#अगर_घोषित macपूर्णांकosh
#आशय options align=reset
#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI__ASM_BOOTX_H__ */
