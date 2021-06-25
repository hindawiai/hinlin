<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_MAJOR_H
#घोषणा _LINUX_MAJOR_H

/*
 * This file has definitions क्रम major device numbers.
 * For the device number assignments, see Documentation/admin-guide/devices.rst.
 */

#घोषणा UNNAMED_MAJOR		0
#घोषणा MEM_MAJOR		1
#घोषणा RAMDISK_MAJOR		1
#घोषणा FLOPPY_MAJOR		2
#घोषणा PTY_MASTER_MAJOR	2
#घोषणा IDE0_MAJOR		3
#घोषणा HD_MAJOR		IDE0_MAJOR
#घोषणा PTY_SLAVE_MAJOR		3
#घोषणा TTY_MAJOR		4
#घोषणा TTYAUX_MAJOR		5
#घोषणा LP_MAJOR		6
#घोषणा VCS_MAJOR		7
#घोषणा LOOP_MAJOR		7
#घोषणा SCSI_DISK0_MAJOR	8
#घोषणा SCSI_TAPE_MAJOR		9
#घोषणा MD_MAJOR		9
#घोषणा MISC_MAJOR		10
#घोषणा SCSI_CDROM_MAJOR	11
#घोषणा MUX_MAJOR		11	/* PA-RISC only */
#घोषणा XT_DISK_MAJOR		13
#घोषणा INPUT_MAJOR		13
#घोषणा SOUND_MAJOR		14
#घोषणा CDU31A_CDROM_MAJOR	15
#घोषणा JOYSTICK_MAJOR		15
#घोषणा GOLDSTAR_CDROM_MAJOR	16
#घोषणा OPTICS_CDROM_MAJOR	17
#घोषणा SANYO_CDROM_MAJOR	18
#घोषणा MITSUMI_X_CDROM_MAJOR	20
#घोषणा MFM_ACORN_MAJOR		21	/* ARM Linux /dev/mfm */
#घोषणा SCSI_GENERIC_MAJOR	21
#घोषणा IDE1_MAJOR		22
#घोषणा DIGICU_MAJOR		22
#घोषणा DIGI_MAJOR		23
#घोषणा MITSUMI_CDROM_MAJOR	23
#घोषणा CDU535_CDROM_MAJOR	24
#घोषणा STL_SERIALMAJOR		24
#घोषणा MATSUSHITA_CDROM_MAJOR	25
#घोषणा STL_CALLOUTMAJOR	25
#घोषणा MATSUSHITA_CDROM2_MAJOR	26
#घोषणा QIC117_TAPE_MAJOR	27
#घोषणा MATSUSHITA_CDROM3_MAJOR	27
#घोषणा MATSUSHITA_CDROM4_MAJOR	28
#घोषणा STL_SIOMEMMAJOR		28
#घोषणा ACSI_MAJOR		28
#घोषणा AZTECH_CDROM_MAJOR	29
#घोषणा FB_MAJOR		29   /* /dev/fb* framebuffers */
#घोषणा MTD_BLOCK_MAJOR		31
#घोषणा CM206_CDROM_MAJOR	32
#घोषणा IDE2_MAJOR		33
#घोषणा IDE3_MAJOR		34
#घोषणा Z8530_MAJOR		34
#घोषणा XPRAM_MAJOR		35   /* Expanded storage on S/390: "slow ram"*/
#घोषणा NETLINK_MAJOR		36
#घोषणा PS2ESDI_MAJOR		36
#घोषणा IDETAPE_MAJOR		37
#घोषणा Z2RAM_MAJOR		37
#घोषणा APBLOCK_MAJOR		38   /* AP1000 Block device */
#घोषणा DDV_MAJOR		39   /* AP1000 DDV block device */
#घोषणा NBD_MAJOR		43   /* Network block device	*/
#घोषणा RISCOM8_NORMAL_MAJOR	48
#घोषणा DAC960_MAJOR		48   /* 48..55 */
#घोषणा RISCOM8_CALLOUT_MAJOR	49
#घोषणा MKISS_MAJOR		55
#घोषणा DSP56K_MAJOR		55   /* DSP56001 processor device */

#घोषणा IDE4_MAJOR		56
#घोषणा IDE5_MAJOR		57

#घोषणा SCSI_DISK1_MAJOR	65
#घोषणा SCSI_DISK2_MAJOR	66
#घोषणा SCSI_DISK3_MAJOR	67
#घोषणा SCSI_DISK4_MAJOR	68
#घोषणा SCSI_DISK5_MAJOR	69
#घोषणा SCSI_DISK6_MAJOR	70
#घोषणा SCSI_DISK7_MAJOR	71

#घोषणा COMPAQ_SMART2_MAJOR	72
#घोषणा COMPAQ_SMART2_MAJOR1	73
#घोषणा COMPAQ_SMART2_MAJOR2	74
#घोषणा COMPAQ_SMART2_MAJOR3	75
#घोषणा COMPAQ_SMART2_MAJOR4	76
#घोषणा COMPAQ_SMART2_MAJOR5	77
#घोषणा COMPAQ_SMART2_MAJOR6	78
#घोषणा COMPAQ_SMART2_MAJOR7	79

#घोषणा SPECIALIX_NORMAL_MAJOR	75
#घोषणा SPECIALIX_CALLOUT_MAJOR	76

#घोषणा AURORA_MAJOR		79

#घोषणा I2O_MAJOR		80	/* 80->87 */

#घोषणा SHMIQ_MAJOR		85   /* Linux/mips, SGI /dev/shmiq */
#घोषणा SCSI_CHANGER_MAJOR      86

#घोषणा IDE6_MAJOR		88
#घोषणा IDE7_MAJOR		89
#घोषणा IDE8_MAJOR		90
#घोषणा MTD_CHAR_MAJOR		90
#घोषणा IDE9_MAJOR		91

#घोषणा DASD_MAJOR		94

#घोषणा MDISK_MAJOR		95

#घोषणा UBD_MAJOR		98

#घोषणा PP_MAJOR		99
#घोषणा JSFD_MAJOR		99

#घोषणा PHONE_MAJOR		100

#घोषणा COMPAQ_CISS_MAJOR	104
#घोषणा COMPAQ_CISS_MAJOR1	105
#घोषणा COMPAQ_CISS_MAJOR2      106
#घोषणा COMPAQ_CISS_MAJOR3      107
#घोषणा COMPAQ_CISS_MAJOR4      108
#घोषणा COMPAQ_CISS_MAJOR5      109
#घोषणा COMPAQ_CISS_MAJOR6      110
#घोषणा COMPAQ_CISS_MAJOR7      111

#घोषणा VIODASD_MAJOR		112
#घोषणा VIOCD_MAJOR		113

#घोषणा ATARAID_MAJOR		114

#घोषणा SCSI_DISK8_MAJOR	128
#घोषणा SCSI_DISK9_MAJOR	129
#घोषणा SCSI_DISK10_MAJOR	130
#घोषणा SCSI_DISK11_MAJOR	131
#घोषणा SCSI_DISK12_MAJOR	132
#घोषणा SCSI_DISK13_MAJOR	133
#घोषणा SCSI_DISK14_MAJOR	134
#घोषणा SCSI_DISK15_MAJOR	135

#घोषणा UNIX98_PTY_MASTER_MAJOR	128
#घोषणा UNIX98_PTY_MAJOR_COUNT	8
#घोषणा UNIX98_PTY_SLAVE_MAJOR	(UNIX98_PTY_MASTER_MAJOR+UNIX98_PTY_MAJOR_COUNT)

#घोषणा DRBD_MAJOR		147
#घोषणा RTF_MAJOR		150
#घोषणा RAW_MAJOR		162

#घोषणा USB_ACM_MAJOR		166
#घोषणा USB_ACM_AUX_MAJOR	167
#घोषणा USB_CHAR_MAJOR		180

#घोषणा MMC_BLOCK_MAJOR		179

#घोषणा VXVM_MAJOR		199	/* VERITAS volume i/o driver    */
#घोषणा VXSPEC_MAJOR		200	/* VERITAS volume config driver */
#घोषणा VXDMP_MAJOR		201	/* VERITAS volume multipath driver */

#घोषणा XENVBD_MAJOR		202	/* Xen भव block device */

#घोषणा MSR_MAJOR		202
#घोषणा CPUID_MAJOR		203

#घोषणा OSST_MAJOR		206	/* OnStream-SCx0 SCSI tape */

#घोषणा IBM_TTY3270_MAJOR	227
#घोषणा IBM_FS3270_MAJOR	228

#घोषणा VIOTAPE_MAJOR		230

#घोषणा BLOCK_EXT_MAJOR		259
#घोषणा SCSI_OSD_MAJOR		260	/* खोलो-osd's OSD scsi device */

#पूर्ण_अगर
