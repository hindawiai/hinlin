<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम ESS Maestro3/Allegro (ES1988) soundcards.
 * Copyright (c) 2000 by Zach Brown <zab@zabbo.net>
 *                       Takashi Iwai <tiwai@suse.de>
 *
 * Most of the hardware init stuffs are based on maestro3 driver क्रम
 * OSS/Free by Zach Brown.  Many thanks to Zach!
 *
 * ChangeLog:
 * Aug. 27, 2001
 *     - Fixed deadlock on capture
 *     - Added Canyon3D-2 support by Rob Riggs <rob@pangalactic.org>
 */
 
#घोषणा CARD_NAME "ESS Maestro3/Allegro/Canyon3D-2"
#घोषणा DRIVER_NAME "Maestro3"

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/input.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>
#समावेश <यंत्र/byteorder.h>

MODULE_AUTHOR("Zach Brown <zab@zabbo.net>, Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("ESS Maestro3 PCI");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("ess/maestro3_assp_kernel.fw");
MODULE_FIRMWARE("ess/maestro3_assp_minisrc.fw");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP; /* all enabled */
अटल bool बाह्यal_amp[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;
अटल पूर्णांक amp_gpio[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = -1पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " CARD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " CARD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable this soundcard.");
module_param_array(बाह्यal_amp, bool, शून्य, 0444);
MODULE_PARM_DESC(बाह्यal_amp, "Enable external amp for " CARD_NAME " soundcard.");
module_param_array(amp_gpio, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(amp_gpio, "GPIO pin number for external amp. (default = -1)");

#घोषणा MAX_PLAYBACKS	2
#घोषणा MAX_CAPTURES	1
#घोषणा NR_DSPS		(MAX_PLAYBACKS + MAX_CAPTURES)


/*
 * maestro3 रेजिस्टरs
 */

/* Allegro PCI configuration रेजिस्टरs */
#घोषणा PCI_LEGACY_AUDIO_CTRL   0x40
#घोषणा SOUND_BLASTER_ENABLE    0x00000001
#घोषणा FM_SYNTHESIS_ENABLE     0x00000002
#घोषणा GAME_PORT_ENABLE        0x00000004
#घोषणा MPU401_IO_ENABLE        0x00000008
#घोषणा MPU401_IRQ_ENABLE       0x00000010
#घोषणा ALIAS_10BIT_IO          0x00000020
#घोषणा SB_DMA_MASK             0x000000C0
#घोषणा SB_DMA_0                0x00000040
#घोषणा SB_DMA_1                0x00000040
#घोषणा SB_DMA_R                0x00000080
#घोषणा SB_DMA_3                0x000000C0
#घोषणा SB_IRQ_MASK             0x00000700
#घोषणा SB_IRQ_5                0x00000000
#घोषणा SB_IRQ_7                0x00000100
#घोषणा SB_IRQ_9                0x00000200
#घोषणा SB_IRQ_10               0x00000300
#घोषणा MIDI_IRQ_MASK           0x00003800
#घोषणा SERIAL_IRQ_ENABLE       0x00004000
#घोषणा DISABLE_LEGACY          0x00008000

#घोषणा PCI_ALLEGRO_CONFIG      0x50
#घोषणा SB_ADDR_240             0x00000004
#घोषणा MPU_ADDR_MASK           0x00000018
#घोषणा MPU_ADDR_330            0x00000000
#घोषणा MPU_ADDR_300            0x00000008
#घोषणा MPU_ADDR_320            0x00000010
#घोषणा MPU_ADDR_340            0x00000018
#घोषणा USE_PCI_TIMING          0x00000040
#घोषणा POSTED_WRITE_ENABLE     0x00000080
#घोषणा DMA_POLICY_MASK         0x00000700
#घोषणा DMA_DDMA                0x00000000
#घोषणा DMA_TDMA                0x00000100
#घोषणा DMA_PCPCI               0x00000200
#घोषणा DMA_WBDMA16             0x00000400
#घोषणा DMA_WBDMA4              0x00000500
#घोषणा DMA_WBDMA2              0x00000600
#घोषणा DMA_WBDMA1              0x00000700
#घोषणा DMA_SAFE_GUARD          0x00000800
#घोषणा HI_PERF_GP_ENABLE       0x00001000
#घोषणा PIC_SNOOP_MODE_0        0x00002000
#घोषणा PIC_SNOOP_MODE_1        0x00004000
#घोषणा SOUNDBLASTER_IRQ_MASK   0x00008000
#घोषणा RING_IN_ENABLE          0x00010000
#घोषणा SPDIF_TEST_MODE         0x00020000
#घोषणा CLK_MULT_MODE_SELECT_2  0x00040000
#घोषणा EEPROM_WRITE_ENABLE     0x00080000
#घोषणा CODEC_सूची_IN            0x00100000
#घोषणा HV_BUTTON_FROM_GD       0x00200000
#घोषणा REDUCED_DEBOUNCE        0x00400000
#घोषणा HV_CTRL_ENABLE          0x00800000
#घोषणा SPDIF_ENABLE            0x01000000
#घोषणा CLK_DIV_SELECT          0x06000000
#घोषणा CLK_DIV_BY_48           0x00000000
#घोषणा CLK_DIV_BY_49           0x02000000
#घोषणा CLK_DIV_BY_50           0x04000000
#घोषणा CLK_DIV_RESERVED        0x06000000
#घोषणा PM_CTRL_ENABLE          0x08000000
#घोषणा CLK_MULT_MODE_SELECT    0x30000000
#घोषणा CLK_MULT_MODE_SHIFT     28
#घोषणा CLK_MULT_MODE_0         0x00000000
#घोषणा CLK_MULT_MODE_1         0x10000000
#घोषणा CLK_MULT_MODE_2         0x20000000
#घोषणा CLK_MULT_MODE_3         0x30000000
#घोषणा INT_CLK_SELECT          0x40000000
#घोषणा INT_CLK_MULT_RESET      0x80000000

/* M3 */
#घोषणा INT_CLK_SRC_NOT_PCI     0x00100000
#घोषणा INT_CLK_MULT_ENABLE     0x80000000

#घोषणा PCI_ACPI_CONTROL        0x54
#घोषणा PCI_ACPI_D0             0x00000000
#घोषणा PCI_ACPI_D1             0xB4F70000
#घोषणा PCI_ACPI_D2             0xB4F7B4F7

#घोषणा PCI_USER_CONFIG         0x58
#घोषणा EXT_PCI_MASTER_ENABLE   0x00000001
#घोषणा SPDIF_OUT_SELECT        0x00000002
#घोषणा TEST_PIN_सूची_CTRL       0x00000004
#घोषणा AC97_CODEC_TEST         0x00000020
#घोषणा TRI_STATE_BUFFER        0x00000080
#घोषणा IN_CLK_12MHZ_SELECT     0x00000100
#घोषणा MULTI_FUNC_DISABLE      0x00000200
#घोषणा EXT_MASTER_PAIR_SEL     0x00000400
#घोषणा PCI_MASTER_SUPPORT      0x00000800
#घोषणा STOP_CLOCK_ENABLE       0x00001000
#घोषणा EAPD_DRIVE_ENABLE       0x00002000
#घोषणा REQ_TRI_STATE_ENABLE    0x00004000
#घोषणा REQ_LOW_ENABLE          0x00008000
#घोषणा MIDI_1_ENABLE           0x00010000
#घोषणा MIDI_2_ENABLE           0x00020000
#घोषणा SB_AUDIO_SYNC           0x00040000
#घोषणा HV_CTRL_TEST            0x00100000
#घोषणा SOUNDBLASTER_TEST       0x00400000

#घोषणा PCI_USER_CONFIG_C       0x5C

#घोषणा PCI_DDMA_CTRL           0x60
#घोषणा DDMA_ENABLE             0x00000001


/* Allegro रेजिस्टरs */
#घोषणा HOST_INT_CTRL           0x18
#घोषणा SB_INT_ENABLE           0x0001
#घोषणा MPU401_INT_ENABLE       0x0002
#घोषणा ASSP_INT_ENABLE         0x0010
#घोषणा RING_INT_ENABLE         0x0020
#घोषणा HV_INT_ENABLE           0x0040
#घोषणा CLKRUN_GEN_ENABLE       0x0100
#घोषणा HV_CTRL_TO_PME          0x0400
#घोषणा SOFTWARE_RESET_ENABLE   0x8000

/*
 * should be using the above defines, probably.
 */
#घोषणा REGB_ENABLE_RESET               0x01
#घोषणा REGB_STOP_CLOCK                 0x10

#घोषणा HOST_INT_STATUS         0x1A
#घोषणा SB_INT_PENDING          0x01
#घोषणा MPU401_INT_PENDING      0x02
#घोषणा ASSP_INT_PENDING        0x10
#घोषणा RING_INT_PENDING        0x20
#घोषणा HV_INT_PENDING          0x40

#घोषणा HARDWARE_VOL_CTRL       0x1B
#घोषणा SHADOW_MIX_REG_VOICE    0x1C
#घोषणा HW_VOL_COUNTER_VOICE    0x1D
#घोषणा SHADOW_MIX_REG_MASTER   0x1E
#घोषणा HW_VOL_COUNTER_MASTER   0x1F

#घोषणा CODEC_COMMAND           0x30
#घोषणा CODEC_READ_B            0x80

#घोषणा CODEC_STATUS            0x30
#घोषणा CODEC_BUSY_B            0x01

#घोषणा CODEC_DATA              0x32

#घोषणा RING_BUS_CTRL_A         0x36
#घोषणा RAC_PME_ENABLE          0x0100
#घोषणा RAC_SDFS_ENABLE         0x0200
#घोषणा LAC_PME_ENABLE          0x0400
#घोषणा LAC_SDFS_ENABLE         0x0800
#घोषणा SERIAL_AC_LINK_ENABLE   0x1000
#घोषणा IO_SRAM_ENABLE          0x2000
#घोषणा IIS_INPUT_ENABLE        0x8000

#घोषणा RING_BUS_CTRL_B         0x38
#घोषणा SECOND_CODEC_ID_MASK    0x0003
#घोषणा SPDIF_FUNC_ENABLE       0x0010
#घोषणा SECOND_AC_ENABLE        0x0020
#घोषणा SB_MODULE_INTF_ENABLE   0x0040
#घोषणा SSPE_ENABLE             0x0040
#घोषणा M3I_DOCK_ENABLE         0x0080

#घोषणा SDO_OUT_DEST_CTRL       0x3A
#घोषणा COMMAND_ADDR_OUT        0x0003
#घोषणा PCM_LR_OUT_LOCAL        0x0000
#घोषणा PCM_LR_OUT_REMOTE       0x0004
#घोषणा PCM_LR_OUT_MUTE         0x0008
#घोषणा PCM_LR_OUT_BOTH         0x000C
#घोषणा LINE1_DAC_OUT_LOCAL     0x0000
#घोषणा LINE1_DAC_OUT_REMOTE    0x0010
#घोषणा LINE1_DAC_OUT_MUTE      0x0020
#घोषणा LINE1_DAC_OUT_BOTH      0x0030
#घोषणा PCM_CLS_OUT_LOCAL       0x0000
#घोषणा PCM_CLS_OUT_REMOTE      0x0040
#घोषणा PCM_CLS_OUT_MUTE        0x0080
#घोषणा PCM_CLS_OUT_BOTH        0x00C0
#घोषणा PCM_RLF_OUT_LOCAL       0x0000
#घोषणा PCM_RLF_OUT_REMOTE      0x0100
#घोषणा PCM_RLF_OUT_MUTE        0x0200
#घोषणा PCM_RLF_OUT_BOTH        0x0300
#घोषणा LINE2_DAC_OUT_LOCAL     0x0000
#घोषणा LINE2_DAC_OUT_REMOTE    0x0400
#घोषणा LINE2_DAC_OUT_MUTE      0x0800
#घोषणा LINE2_DAC_OUT_BOTH      0x0C00
#घोषणा HANDSET_OUT_LOCAL       0x0000
#घोषणा HANDSET_OUT_REMOTE      0x1000
#घोषणा HANDSET_OUT_MUTE        0x2000
#घोषणा HANDSET_OUT_BOTH        0x3000
#घोषणा IO_CTRL_OUT_LOCAL       0x0000
#घोषणा IO_CTRL_OUT_REMOTE      0x4000
#घोषणा IO_CTRL_OUT_MUTE        0x8000
#घोषणा IO_CTRL_OUT_BOTH        0xC000

#घोषणा SDO_IN_DEST_CTRL        0x3C
#घोषणा STATUS_ADDR_IN          0x0003
#घोषणा PCM_LR_IN_LOCAL         0x0000
#घोषणा PCM_LR_IN_REMOTE        0x0004
#घोषणा PCM_LR_RESERVED         0x0008
#घोषणा PCM_LR_IN_BOTH          0x000C
#घोषणा LINE1_ADC_IN_LOCAL      0x0000
#घोषणा LINE1_ADC_IN_REMOTE     0x0010
#घोषणा LINE1_ADC_IN_MUTE       0x0020
#घोषणा MIC_ADC_IN_LOCAL        0x0000
#घोषणा MIC_ADC_IN_REMOTE       0x0040
#घोषणा MIC_ADC_IN_MUTE         0x0080
#घोषणा LINE2_DAC_IN_LOCAL      0x0000
#घोषणा LINE2_DAC_IN_REMOTE     0x0400
#घोषणा LINE2_DAC_IN_MUTE       0x0800
#घोषणा HANDSET_IN_LOCAL        0x0000
#घोषणा HANDSET_IN_REMOTE       0x1000
#घोषणा HANDSET_IN_MUTE         0x2000
#घोषणा IO_STATUS_IN_LOCAL      0x0000
#घोषणा IO_STATUS_IN_REMOTE     0x4000

#घोषणा SPDIF_IN_CTRL           0x3E
#घोषणा SPDIF_IN_ENABLE         0x0001

#घोषणा GPIO_DATA               0x60
#घोषणा GPIO_DATA_MASK          0x0FFF
#घोषणा GPIO_HV_STATUS          0x3000
#घोषणा GPIO_PME_STATUS         0x4000

#घोषणा GPIO_MASK               0x64
#घोषणा GPIO_सूचीECTION          0x68
#घोषणा GPO_PRIMARY_AC97        0x0001
#घोषणा GPI_LINEOUT_SENSE       0x0004
#घोषणा GPO_SECONDARY_AC97      0x0008
#घोषणा GPI_VOL_DOWN            0x0010
#घोषणा GPI_VOL_UP              0x0020
#घोषणा GPI_IIS_CLK             0x0040
#घोषणा GPI_IIS_LRCLK           0x0080
#घोषणा GPI_IIS_DATA            0x0100
#घोषणा GPI_DOCKING_STATUS      0x0100
#घोषणा GPI_HEADPHONE_SENSE     0x0200
#घोषणा GPO_EXT_AMP_SHUTDOWN    0x1000

#घोषणा GPO_EXT_AMP_M3		1	/* शेष m3 amp */
#घोषणा GPO_EXT_AMP_ALLEGRO	8	/* शेष allegro amp */

/* M3 */
#घोषणा GPO_M3_EXT_AMP_SHUTDN   0x0002

#घोषणा ASSP_INDEX_PORT         0x80
#घोषणा ASSP_MEMORY_PORT        0x82
#घोषणा ASSP_DATA_PORT          0x84

#घोषणा MPU401_DATA_PORT        0x98
#घोषणा MPU401_STATUS_PORT      0x99

#घोषणा CLK_MULT_DATA_PORT      0x9C

#घोषणा ASSP_CONTROL_A          0xA2
#घोषणा ASSP_0_WS_ENABLE        0x01
#घोषणा ASSP_CTRL_A_RESERVED1   0x02
#घोषणा ASSP_CTRL_A_RESERVED2   0x04
#घोषणा ASSP_CLK_49MHZ_SELECT   0x08
#घोषणा FAST_PLU_ENABLE         0x10
#घोषणा ASSP_CTRL_A_RESERVED3   0x20
#घोषणा DSP_CLK_36MHZ_SELECT    0x40

#घोषणा ASSP_CONTROL_B          0xA4
#घोषणा RESET_ASSP              0x00
#घोषणा RUN_ASSP                0x01
#घोषणा ENABLE_ASSP_CLOCK       0x00
#घोषणा STOP_ASSP_CLOCK         0x10
#घोषणा RESET_TOGGLE            0x40

#घोषणा ASSP_CONTROL_C          0xA6
#घोषणा ASSP_HOST_INT_ENABLE    0x01
#घोषणा FM_ADDR_REMAP_DISABLE   0x02
#घोषणा HOST_WRITE_PORT_ENABLE  0x08

#घोषणा ASSP_HOST_INT_STATUS    0xAC
#घोषणा DSP2HOST_REQ_PIORECORD  0x01
#घोषणा DSP2HOST_REQ_I2SRATE    0x02
#घोषणा DSP2HOST_REQ_TIMER      0x04

/*
 * ASSP control regs
 */
#घोषणा DSP_PORT_TIMER_COUNT    0x06

#घोषणा DSP_PORT_MEMORY_INDEX   0x80

#घोषणा DSP_PORT_MEMORY_TYPE    0x82
#घोषणा MEMTYPE_INTERNAL_CODE   0x0002
#घोषणा MEMTYPE_INTERNAL_DATA   0x0003
#घोषणा MEMTYPE_MASK            0x0003

#घोषणा DSP_PORT_MEMORY_DATA    0x84

#घोषणा DSP_PORT_CONTROL_REG_A  0xA2
#घोषणा DSP_PORT_CONTROL_REG_B  0xA4
#घोषणा DSP_PORT_CONTROL_REG_C  0xA6

#घोषणा REV_A_CODE_MEMORY_BEGIN         0x0000
#घोषणा REV_A_CODE_MEMORY_END           0x0FFF
#घोषणा REV_A_CODE_MEMORY_UNIT_LENGTH   0x0040
#घोषणा REV_A_CODE_MEMORY_LENGTH        (REV_A_CODE_MEMORY_END - REV_A_CODE_MEMORY_BEGIN + 1)

#घोषणा REV_B_CODE_MEMORY_BEGIN         0x0000
#घोषणा REV_B_CODE_MEMORY_END           0x0BFF
#घोषणा REV_B_CODE_MEMORY_UNIT_LENGTH   0x0040
#घोषणा REV_B_CODE_MEMORY_LENGTH        (REV_B_CODE_MEMORY_END - REV_B_CODE_MEMORY_BEGIN + 1)

#घोषणा REV_A_DATA_MEMORY_BEGIN         0x1000
#घोषणा REV_A_DATA_MEMORY_END           0x2FFF
#घोषणा REV_A_DATA_MEMORY_UNIT_LENGTH   0x0080
#घोषणा REV_A_DATA_MEMORY_LENGTH        (REV_A_DATA_MEMORY_END - REV_A_DATA_MEMORY_BEGIN + 1)

#घोषणा REV_B_DATA_MEMORY_BEGIN         0x1000
#घोषणा REV_B_DATA_MEMORY_END           0x2BFF
#घोषणा REV_B_DATA_MEMORY_UNIT_LENGTH   0x0080
#घोषणा REV_B_DATA_MEMORY_LENGTH        (REV_B_DATA_MEMORY_END - REV_B_DATA_MEMORY_BEGIN + 1)


#घोषणा NUM_UNITS_KERNEL_CODE          16
#घोषणा NUM_UNITS_KERNEL_DATA           2

#घोषणा NUM_UNITS_KERNEL_CODE_WITH_HSP 16
#घोषणा NUM_UNITS_KERNEL_DATA_WITH_HSP  5

/*
 * Kernel data layout
 */

#घोषणा DP_SHIFT_COUNT                  7

#घोषणा KDATA_BASE_ADDR                 0x1000
#घोषणा KDATA_BASE_ADDR2                0x1080

#घोषणा KDATA_TASK0                     (KDATA_BASE_ADDR + 0x0000)
#घोषणा KDATA_TASK1                     (KDATA_BASE_ADDR + 0x0001)
#घोषणा KDATA_TASK2                     (KDATA_BASE_ADDR + 0x0002)
#घोषणा KDATA_TASK3                     (KDATA_BASE_ADDR + 0x0003)
#घोषणा KDATA_TASK4                     (KDATA_BASE_ADDR + 0x0004)
#घोषणा KDATA_TASK5                     (KDATA_BASE_ADDR + 0x0005)
#घोषणा KDATA_TASK6                     (KDATA_BASE_ADDR + 0x0006)
#घोषणा KDATA_TASK7                     (KDATA_BASE_ADDR + 0x0007)
#घोषणा KDATA_TASK_ENDMARK              (KDATA_BASE_ADDR + 0x0008)

#घोषणा KDATA_CURRENT_TASK              (KDATA_BASE_ADDR + 0x0009)
#घोषणा KDATA_TASK_SWITCH               (KDATA_BASE_ADDR + 0x000A)

#घोषणा KDATA_INSTANCE0_POS3D           (KDATA_BASE_ADDR + 0x000B)
#घोषणा KDATA_INSTANCE1_POS3D           (KDATA_BASE_ADDR + 0x000C)
#घोषणा KDATA_INSTANCE2_POS3D           (KDATA_BASE_ADDR + 0x000D)
#घोषणा KDATA_INSTANCE3_POS3D           (KDATA_BASE_ADDR + 0x000E)
#घोषणा KDATA_INSTANCE4_POS3D           (KDATA_BASE_ADDR + 0x000F)
#घोषणा KDATA_INSTANCE5_POS3D           (KDATA_BASE_ADDR + 0x0010)
#घोषणा KDATA_INSTANCE6_POS3D           (KDATA_BASE_ADDR + 0x0011)
#घोषणा KDATA_INSTANCE7_POS3D           (KDATA_BASE_ADDR + 0x0012)
#घोषणा KDATA_INSTANCE8_POS3D           (KDATA_BASE_ADDR + 0x0013)
#घोषणा KDATA_INSTANCE_POS3D_ENDMARK    (KDATA_BASE_ADDR + 0x0014)

#घोषणा KDATA_INSTANCE0_SPKVIRT         (KDATA_BASE_ADDR + 0x0015)
#घोषणा KDATA_INSTANCE_SPKVIRT_ENDMARK  (KDATA_BASE_ADDR + 0x0016)

#घोषणा KDATA_INSTANCE0_SPDIF           (KDATA_BASE_ADDR + 0x0017)
#घोषणा KDATA_INSTANCE_SPDIF_ENDMARK    (KDATA_BASE_ADDR + 0x0018)

#घोषणा KDATA_INSTANCE0_MODEM           (KDATA_BASE_ADDR + 0x0019)
#घोषणा KDATA_INSTANCE_MODEM_ENDMARK    (KDATA_BASE_ADDR + 0x001A)

#घोषणा KDATA_INSTANCE0_SRC             (KDATA_BASE_ADDR + 0x001B)
#घोषणा KDATA_INSTANCE1_SRC             (KDATA_BASE_ADDR + 0x001C)
#घोषणा KDATA_INSTANCE_SRC_ENDMARK      (KDATA_BASE_ADDR + 0x001D)

#घोषणा KDATA_INSTANCE0_MINISRC         (KDATA_BASE_ADDR + 0x001E)
#घोषणा KDATA_INSTANCE1_MINISRC         (KDATA_BASE_ADDR + 0x001F)
#घोषणा KDATA_INSTANCE2_MINISRC         (KDATA_BASE_ADDR + 0x0020)
#घोषणा KDATA_INSTANCE3_MINISRC         (KDATA_BASE_ADDR + 0x0021)
#घोषणा KDATA_INSTANCE_MINISRC_ENDMARK  (KDATA_BASE_ADDR + 0x0022)

#घोषणा KDATA_INSTANCE0_CPYTHRU         (KDATA_BASE_ADDR + 0x0023)
#घोषणा KDATA_INSTANCE1_CPYTHRU         (KDATA_BASE_ADDR + 0x0024)
#घोषणा KDATA_INSTANCE_CPYTHRU_ENDMARK  (KDATA_BASE_ADDR + 0x0025)

#घोषणा KDATA_CURRENT_DMA               (KDATA_BASE_ADDR + 0x0026)
#घोषणा KDATA_DMA_SWITCH                (KDATA_BASE_ADDR + 0x0027)
#घोषणा KDATA_DMA_ACTIVE                (KDATA_BASE_ADDR + 0x0028)

#घोषणा KDATA_DMA_XFER0                 (KDATA_BASE_ADDR + 0x0029)
#घोषणा KDATA_DMA_XFER1                 (KDATA_BASE_ADDR + 0x002A)
#घोषणा KDATA_DMA_XFER2                 (KDATA_BASE_ADDR + 0x002B)
#घोषणा KDATA_DMA_XFER3                 (KDATA_BASE_ADDR + 0x002C)
#घोषणा KDATA_DMA_XFER4                 (KDATA_BASE_ADDR + 0x002D)
#घोषणा KDATA_DMA_XFER5                 (KDATA_BASE_ADDR + 0x002E)
#घोषणा KDATA_DMA_XFER6                 (KDATA_BASE_ADDR + 0x002F)
#घोषणा KDATA_DMA_XFER7                 (KDATA_BASE_ADDR + 0x0030)
#घोषणा KDATA_DMA_XFER8                 (KDATA_BASE_ADDR + 0x0031)
#घोषणा KDATA_DMA_XFER_ENDMARK          (KDATA_BASE_ADDR + 0x0032)

#घोषणा KDATA_I2S_SAMPLE_COUNT          (KDATA_BASE_ADDR + 0x0033)
#घोषणा KDATA_I2S_INT_METER             (KDATA_BASE_ADDR + 0x0034)
#घोषणा KDATA_I2S_ACTIVE                (KDATA_BASE_ADDR + 0x0035)

#घोषणा KDATA_TIMER_COUNT_RELOAD        (KDATA_BASE_ADDR + 0x0036)
#घोषणा KDATA_TIMER_COUNT_CURRENT       (KDATA_BASE_ADDR + 0x0037)

#घोषणा KDATA_HALT_SYNCH_CLIENT         (KDATA_BASE_ADDR + 0x0038)
#घोषणा KDATA_HALT_SYNCH_DMA            (KDATA_BASE_ADDR + 0x0039)
#घोषणा KDATA_HALT_ACKNOWLEDGE          (KDATA_BASE_ADDR + 0x003A)

#घोषणा KDATA_ADC1_XFER0                (KDATA_BASE_ADDR + 0x003B)
#घोषणा KDATA_ADC1_XFER_ENDMARK         (KDATA_BASE_ADDR + 0x003C)
#घोषणा KDATA_ADC1_LEFT_VOLUME			(KDATA_BASE_ADDR + 0x003D)
#घोषणा KDATA_ADC1_RIGHT_VOLUME  		(KDATA_BASE_ADDR + 0x003E)
#घोषणा KDATA_ADC1_LEFT_SUR_VOL			(KDATA_BASE_ADDR + 0x003F)
#घोषणा KDATA_ADC1_RIGHT_SUR_VOL		(KDATA_BASE_ADDR + 0x0040)

#घोषणा KDATA_ADC2_XFER0                (KDATA_BASE_ADDR + 0x0041)
#घोषणा KDATA_ADC2_XFER_ENDMARK         (KDATA_BASE_ADDR + 0x0042)
#घोषणा KDATA_ADC2_LEFT_VOLUME			(KDATA_BASE_ADDR + 0x0043)
#घोषणा KDATA_ADC2_RIGHT_VOLUME			(KDATA_BASE_ADDR + 0x0044)
#घोषणा KDATA_ADC2_LEFT_SUR_VOL			(KDATA_BASE_ADDR + 0x0045)
#घोषणा KDATA_ADC2_RIGHT_SUR_VOL		(KDATA_BASE_ADDR + 0x0046)

#घोषणा KDATA_CD_XFER0					(KDATA_BASE_ADDR + 0x0047)					
#घोषणा KDATA_CD_XFER_ENDMARK			(KDATA_BASE_ADDR + 0x0048)
#घोषणा KDATA_CD_LEFT_VOLUME			(KDATA_BASE_ADDR + 0x0049)
#घोषणा KDATA_CD_RIGHT_VOLUME			(KDATA_BASE_ADDR + 0x004A)
#घोषणा KDATA_CD_LEFT_SUR_VOL			(KDATA_BASE_ADDR + 0x004B)
#घोषणा KDATA_CD_RIGHT_SUR_VOL			(KDATA_BASE_ADDR + 0x004C)

#घोषणा KDATA_MIC_XFER0					(KDATA_BASE_ADDR + 0x004D)
#घोषणा KDATA_MIC_XFER_ENDMARK			(KDATA_BASE_ADDR + 0x004E)
#घोषणा KDATA_MIC_VOLUME				(KDATA_BASE_ADDR + 0x004F)
#घोषणा KDATA_MIC_SUR_VOL				(KDATA_BASE_ADDR + 0x0050)

#घोषणा KDATA_I2S_XFER0                 (KDATA_BASE_ADDR + 0x0051)
#घोषणा KDATA_I2S_XFER_ENDMARK          (KDATA_BASE_ADDR + 0x0052)

#घोषणा KDATA_CHI_XFER0                 (KDATA_BASE_ADDR + 0x0053)
#घोषणा KDATA_CHI_XFER_ENDMARK          (KDATA_BASE_ADDR + 0x0054)

#घोषणा KDATA_SPDIF_XFER                (KDATA_BASE_ADDR + 0x0055)
#घोषणा KDATA_SPDIF_CURRENT_FRAME       (KDATA_BASE_ADDR + 0x0056)
#घोषणा KDATA_SPDIF_FRAME0              (KDATA_BASE_ADDR + 0x0057)
#घोषणा KDATA_SPDIF_FRAME1              (KDATA_BASE_ADDR + 0x0058)
#घोषणा KDATA_SPDIF_FRAME2              (KDATA_BASE_ADDR + 0x0059)

#घोषणा KDATA_SPDIF_REQUEST             (KDATA_BASE_ADDR + 0x005A)
#घोषणा KDATA_SPDIF_TEMP                (KDATA_BASE_ADDR + 0x005B)

#घोषणा KDATA_SPDIFIN_XFER0             (KDATA_BASE_ADDR + 0x005C)
#घोषणा KDATA_SPDIFIN_XFER_ENDMARK      (KDATA_BASE_ADDR + 0x005D)
#घोषणा KDATA_SPDIFIN_INT_METER         (KDATA_BASE_ADDR + 0x005E)

#घोषणा KDATA_DSP_RESET_COUNT           (KDATA_BASE_ADDR + 0x005F)
#घोषणा KDATA_DEBUG_OUTPUT              (KDATA_BASE_ADDR + 0x0060)

#घोषणा KDATA_KERNEL_ISR_LIST           (KDATA_BASE_ADDR + 0x0061)

#घोषणा KDATA_KERNEL_ISR_CBSR1          (KDATA_BASE_ADDR + 0x0062)
#घोषणा KDATA_KERNEL_ISR_CBER1          (KDATA_BASE_ADDR + 0x0063)
#घोषणा KDATA_KERNEL_ISR_CBCR           (KDATA_BASE_ADDR + 0x0064)
#घोषणा KDATA_KERNEL_ISR_AR0            (KDATA_BASE_ADDR + 0x0065)
#घोषणा KDATA_KERNEL_ISR_AR1            (KDATA_BASE_ADDR + 0x0066)
#घोषणा KDATA_KERNEL_ISR_AR2            (KDATA_BASE_ADDR + 0x0067)
#घोषणा KDATA_KERNEL_ISR_AR3            (KDATA_BASE_ADDR + 0x0068)
#घोषणा KDATA_KERNEL_ISR_AR4            (KDATA_BASE_ADDR + 0x0069)
#घोषणा KDATA_KERNEL_ISR_AR5            (KDATA_BASE_ADDR + 0x006A)
#घोषणा KDATA_KERNEL_ISR_BRCR           (KDATA_BASE_ADDR + 0x006B)
#घोषणा KDATA_KERNEL_ISR_PASR           (KDATA_BASE_ADDR + 0x006C)
#घोषणा KDATA_KERNEL_ISR_PAER           (KDATA_BASE_ADDR + 0x006D)

#घोषणा KDATA_CLIENT_SCRATCH0           (KDATA_BASE_ADDR + 0x006E)
#घोषणा KDATA_CLIENT_SCRATCH1           (KDATA_BASE_ADDR + 0x006F)
#घोषणा KDATA_KERNEL_SCRATCH            (KDATA_BASE_ADDR + 0x0070)
#घोषणा KDATA_KERNEL_ISR_SCRATCH        (KDATA_BASE_ADDR + 0x0071)

#घोषणा KDATA_OUEUE_LEFT                (KDATA_BASE_ADDR + 0x0072)
#घोषणा KDATA_QUEUE_RIGHT               (KDATA_BASE_ADDR + 0x0073)

#घोषणा KDATA_ADC1_REQUEST              (KDATA_BASE_ADDR + 0x0074)
#घोषणा KDATA_ADC2_REQUEST              (KDATA_BASE_ADDR + 0x0075)
#घोषणा KDATA_CD_REQUEST				(KDATA_BASE_ADDR + 0x0076)
#घोषणा KDATA_MIC_REQUEST				(KDATA_BASE_ADDR + 0x0077)

#घोषणा KDATA_ADC1_MIXER_REQUEST        (KDATA_BASE_ADDR + 0x0078)
#घोषणा KDATA_ADC2_MIXER_REQUEST        (KDATA_BASE_ADDR + 0x0079)
#घोषणा KDATA_CD_MIXER_REQUEST			(KDATA_BASE_ADDR + 0x007A)
#घोषणा KDATA_MIC_MIXER_REQUEST			(KDATA_BASE_ADDR + 0x007B)
#घोषणा KDATA_MIC_SYNC_COUNTER			(KDATA_BASE_ADDR + 0x007C)

/*
 * second 'segment' (?) reserved क्रम mixer
 * buffers..
 */

#घोषणा KDATA_MIXER_WORD0               (KDATA_BASE_ADDR2 + 0x0000)
#घोषणा KDATA_MIXER_WORD1               (KDATA_BASE_ADDR2 + 0x0001)
#घोषणा KDATA_MIXER_WORD2               (KDATA_BASE_ADDR2 + 0x0002)
#घोषणा KDATA_MIXER_WORD3               (KDATA_BASE_ADDR2 + 0x0003)
#घोषणा KDATA_MIXER_WORD4               (KDATA_BASE_ADDR2 + 0x0004)
#घोषणा KDATA_MIXER_WORD5               (KDATA_BASE_ADDR2 + 0x0005)
#घोषणा KDATA_MIXER_WORD6               (KDATA_BASE_ADDR2 + 0x0006)
#घोषणा KDATA_MIXER_WORD7               (KDATA_BASE_ADDR2 + 0x0007)
#घोषणा KDATA_MIXER_WORD8               (KDATA_BASE_ADDR2 + 0x0008)
#घोषणा KDATA_MIXER_WORD9               (KDATA_BASE_ADDR2 + 0x0009)
#घोषणा KDATA_MIXER_WORDA               (KDATA_BASE_ADDR2 + 0x000A)
#घोषणा KDATA_MIXER_WORDB               (KDATA_BASE_ADDR2 + 0x000B)
#घोषणा KDATA_MIXER_WORDC               (KDATA_BASE_ADDR2 + 0x000C)
#घोषणा KDATA_MIXER_WORDD               (KDATA_BASE_ADDR2 + 0x000D)
#घोषणा KDATA_MIXER_WORDE               (KDATA_BASE_ADDR2 + 0x000E)
#घोषणा KDATA_MIXER_WORDF               (KDATA_BASE_ADDR2 + 0x000F)

#घोषणा KDATA_MIXER_XFER0               (KDATA_BASE_ADDR2 + 0x0010)
#घोषणा KDATA_MIXER_XFER1               (KDATA_BASE_ADDR2 + 0x0011)
#घोषणा KDATA_MIXER_XFER2               (KDATA_BASE_ADDR2 + 0x0012)
#घोषणा KDATA_MIXER_XFER3               (KDATA_BASE_ADDR2 + 0x0013)
#घोषणा KDATA_MIXER_XFER4               (KDATA_BASE_ADDR2 + 0x0014)
#घोषणा KDATA_MIXER_XFER5               (KDATA_BASE_ADDR2 + 0x0015)
#घोषणा KDATA_MIXER_XFER6               (KDATA_BASE_ADDR2 + 0x0016)
#घोषणा KDATA_MIXER_XFER7               (KDATA_BASE_ADDR2 + 0x0017)
#घोषणा KDATA_MIXER_XFER8               (KDATA_BASE_ADDR2 + 0x0018)
#घोषणा KDATA_MIXER_XFER9               (KDATA_BASE_ADDR2 + 0x0019)
#घोषणा KDATA_MIXER_XFER_ENDMARK        (KDATA_BASE_ADDR2 + 0x001A)

#घोषणा KDATA_MIXER_TASK_NUMBER         (KDATA_BASE_ADDR2 + 0x001B)
#घोषणा KDATA_CURRENT_MIXER             (KDATA_BASE_ADDR2 + 0x001C)
#घोषणा KDATA_MIXER_ACTIVE              (KDATA_BASE_ADDR2 + 0x001D)
#घोषणा KDATA_MIXER_BANK_STATUS         (KDATA_BASE_ADDR2 + 0x001E)
#घोषणा KDATA_DAC_LEFT_VOLUME	        (KDATA_BASE_ADDR2 + 0x001F)
#घोषणा KDATA_DAC_RIGHT_VOLUME          (KDATA_BASE_ADDR2 + 0x0020)

#घोषणा MAX_INSTANCE_MINISRC            (KDATA_INSTANCE_MINISRC_ENDMARK - KDATA_INSTANCE0_MINISRC)
#घोषणा MAX_VIRTUAL_DMA_CHANNELS        (KDATA_DMA_XFER_ENDMARK - KDATA_DMA_XFER0)
#घोषणा MAX_VIRTUAL_MIXER_CHANNELS      (KDATA_MIXER_XFER_ENDMARK - KDATA_MIXER_XFER0)
#घोषणा MAX_VIRTUAL_ADC1_CHANNELS       (KDATA_ADC1_XFER_ENDMARK - KDATA_ADC1_XFER0)

/*
 * client data area offsets
 */
#घोषणा CDATA_INSTANCE_READY            0x00

#घोषणा CDATA_HOST_SRC_ADDRL            0x01
#घोषणा CDATA_HOST_SRC_ADDRH            0x02
#घोषणा CDATA_HOST_SRC_END_PLUS_1L      0x03
#घोषणा CDATA_HOST_SRC_END_PLUS_1H      0x04
#घोषणा CDATA_HOST_SRC_CURRENTL         0x05
#घोषणा CDATA_HOST_SRC_CURRENTH         0x06

#घोषणा CDATA_IN_BUF_CONNECT            0x07
#घोषणा CDATA_OUT_BUF_CONNECT           0x08

#घोषणा CDATA_IN_BUF_BEGIN              0x09
#घोषणा CDATA_IN_BUF_END_PLUS_1         0x0A
#घोषणा CDATA_IN_BUF_HEAD               0x0B
#घोषणा CDATA_IN_BUF_TAIL               0x0C
#घोषणा CDATA_OUT_BUF_BEGIN             0x0D
#घोषणा CDATA_OUT_BUF_END_PLUS_1        0x0E
#घोषणा CDATA_OUT_BUF_HEAD              0x0F
#घोषणा CDATA_OUT_BUF_TAIL              0x10

#घोषणा CDATA_DMA_CONTROL               0x11
#घोषणा CDATA_RESERVED                  0x12

#घोषणा CDATA_FREQUENCY                 0x13
#घोषणा CDATA_LEFT_VOLUME               0x14
#घोषणा CDATA_RIGHT_VOLUME              0x15
#घोषणा CDATA_LEFT_SUR_VOL              0x16
#घोषणा CDATA_RIGHT_SUR_VOL             0x17

#घोषणा CDATA_HEADER_LEN                0x18

#घोषणा SRC3_सूचीECTION_OFFSET           CDATA_HEADER_LEN
#घोषणा SRC3_MODE_OFFSET                (CDATA_HEADER_LEN + 1)
#घोषणा SRC3_WORD_LENGTH_OFFSET         (CDATA_HEADER_LEN + 2)
#घोषणा SRC3_PARAMETER_OFFSET           (CDATA_HEADER_LEN + 3)
#घोषणा SRC3_COEFF_ADDR_OFFSET          (CDATA_HEADER_LEN + 8)
#घोषणा SRC3_FILTAP_ADDR_OFFSET         (CDATA_HEADER_LEN + 10)
#घोषणा SRC3_TEMP_INBUF_ADDR_OFFSET     (CDATA_HEADER_LEN + 16)
#घोषणा SRC3_TEMP_OUTBUF_ADDR_OFFSET    (CDATA_HEADER_LEN + 17)

#घोषणा MINISRC_IN_BUFFER_SIZE   ( 0x50 * 2 )
#घोषणा MINISRC_OUT_BUFFER_SIZE  ( 0x50 * 2 * 2)
#घोषणा MINISRC_TMP_BUFFER_SIZE  ( 112 + ( MINISRC_BIQUAD_STAGE * 3 + 4 ) * 2 * 2 )
#घोषणा MINISRC_BIQUAD_STAGE    2
#घोषणा MINISRC_COEF_LOC          0x175

#घोषणा DMACONTROL_BLOCK_MASK           0x000F
#घोषणा  DMAC_BLOCK0_SELECTOR           0x0000
#घोषणा  DMAC_BLOCK1_SELECTOR           0x0001
#घोषणा  DMAC_BLOCK2_SELECTOR           0x0002
#घोषणा  DMAC_BLOCK3_SELECTOR           0x0003
#घोषणा  DMAC_BLOCK4_SELECTOR           0x0004
#घोषणा  DMAC_BLOCK5_SELECTOR           0x0005
#घोषणा  DMAC_BLOCK6_SELECTOR           0x0006
#घोषणा  DMAC_BLOCK7_SELECTOR           0x0007
#घोषणा  DMAC_BLOCK8_SELECTOR           0x0008
#घोषणा  DMAC_BLOCK9_SELECTOR           0x0009
#घोषणा  DMAC_BLOCKA_SELECTOR           0x000A
#घोषणा  DMAC_BLOCKB_SELECTOR           0x000B
#घोषणा  DMAC_BLOCKC_SELECTOR           0x000C
#घोषणा  DMAC_BLOCKD_SELECTOR           0x000D
#घोषणा  DMAC_BLOCKE_SELECTOR           0x000E
#घोषणा  DMAC_BLOCKF_SELECTOR           0x000F
#घोषणा DMACONTROL_PAGE_MASK            0x00F0
#घोषणा  DMAC_PAGE0_SELECTOR            0x0030
#घोषणा  DMAC_PAGE1_SELECTOR            0x0020
#घोषणा  DMAC_PAGE2_SELECTOR            0x0010
#घोषणा  DMAC_PAGE3_SELECTOR            0x0000
#घोषणा DMACONTROL_AUTOREPEAT           0x1000
#घोषणा DMACONTROL_STOPPED              0x2000
#घोषणा DMACONTROL_सूचीECTION            0x0100

/*
 * an arbitrary volume we set the पूर्णांकernal
 * volume settings to so that the ac97 volume
 * range is a little less insane.  0x7fff is 
 * max.
 */
#घोषणा ARB_VOLUME ( 0x6800 )

/*
 */

काष्ठा m3_list अणु
	पूर्णांक curlen;
	पूर्णांक mem_addr;
	पूर्णांक max;
पूर्ण;

काष्ठा m3_dma अणु

	पूर्णांक number;
	काष्ठा snd_pcm_substream *substream;

	काष्ठा assp_instance अणु
		अचिन्हित लघु code, data;
	पूर्ण inst;

	पूर्णांक running;
	पूर्णांक खोलोed;

	अचिन्हित दीर्घ buffer_addr;
	पूर्णांक dma_size;
	पूर्णांक period_size;
	अचिन्हित पूर्णांक hwptr;
	पूर्णांक count;

	पूर्णांक index[3];
	काष्ठा m3_list *index_list[3];

        पूर्णांक in_lists;
	
	काष्ठा list_head list;

पूर्ण;
    
काष्ठा snd_m3 अणु
	
	काष्ठा snd_card *card;

	अचिन्हित दीर्घ iobase;

	पूर्णांक irq;
	अचिन्हित पूर्णांक allegro_flag : 1;

	काष्ठा snd_ac97 *ac97;

	काष्ठा snd_pcm *pcm;

	काष्ठा pci_dev *pci;

	पूर्णांक dacs_active;
	पूर्णांक समयr_users;

	काष्ठा m3_list  msrc_list;
	काष्ठा m3_list  mixer_list;
	काष्ठा m3_list  adc1_list;
	काष्ठा m3_list  dma_list;

	/* क्रम storing reset state..*/
	u8 reset_state;

	पूर्णांक बाह्यal_amp;
	पूर्णांक amp_gpio;	/* gpio pin #  क्रम बाह्यal amp, -1 = शेष */
	अचिन्हित पूर्णांक hv_config;		/* hardware-volume config bits */
	अचिन्हित irda_workaround :1;	/* aव्योम to touch 0x10 on GPIO_सूचीECTION
					   (e.g. क्रम IrDA on Dell Inspirons) */
	अचिन्हित is_omnibook :1;	/* Do HP OmniBook GPIO magic? */

	/* midi */
	काष्ठा snd_rawmidi *rmidi;

	/* pcm streams */
	पूर्णांक num_substreams;
	काष्ठा m3_dma *substreams;

	spinlock_t reg_lock;

#अगर_घोषित CONFIG_SND_MAESTRO3_INPUT
	काष्ठा input_dev *input_dev;
	अक्षर phys[64];			/* physical device path */
#अन्यथा
	काष्ठा snd_kcontrol *master_चयन;
	काष्ठा snd_kcontrol *master_volume;
#पूर्ण_अगर
	काष्ठा work_काष्ठा hwvol_work;

	अचिन्हित पूर्णांक in_suspend;

#अगर_घोषित CONFIG_PM_SLEEP
	u16 *suspend_mem;
#पूर्ण_अगर

	स्थिर काष्ठा firmware *assp_kernel_image;
	स्थिर काष्ठा firmware *assp_minisrc_image;
पूर्ण;

/*
 * pci ids
 */
अटल स्थिर काष्ठा pci_device_id snd_m3_ids[] = अणु
	अणुPCI_VENDOR_ID_ESS, PCI_DEVICE_ID_ESS_ALLEGRO_1, PCI_ANY_ID, PCI_ANY_ID,
	 PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, 0पूर्ण,
	अणुPCI_VENDOR_ID_ESS, PCI_DEVICE_ID_ESS_ALLEGRO, PCI_ANY_ID, PCI_ANY_ID,
	 PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, 0पूर्ण,
	अणुPCI_VENDOR_ID_ESS, PCI_DEVICE_ID_ESS_CANYON3D_2LE, PCI_ANY_ID, PCI_ANY_ID,
	 PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, 0पूर्ण,
	अणुPCI_VENDOR_ID_ESS, PCI_DEVICE_ID_ESS_CANYON3D_2, PCI_ANY_ID, PCI_ANY_ID,
	 PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, 0पूर्ण,
	अणुPCI_VENDOR_ID_ESS, PCI_DEVICE_ID_ESS_MAESTRO3, PCI_ANY_ID, PCI_ANY_ID,
	 PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, 0पूर्ण,
	अणुPCI_VENDOR_ID_ESS, PCI_DEVICE_ID_ESS_MAESTRO3_1, PCI_ANY_ID, PCI_ANY_ID,
	 PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, 0पूर्ण,
	अणुPCI_VENDOR_ID_ESS, PCI_DEVICE_ID_ESS_MAESTRO3_HW, PCI_ANY_ID, PCI_ANY_ID,
	 PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, 0पूर्ण,
	अणुPCI_VENDOR_ID_ESS, PCI_DEVICE_ID_ESS_MAESTRO3_2, PCI_ANY_ID, PCI_ANY_ID,
	 PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, 0पूर्ण,
	अणु0,पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_m3_ids);

अटल स्थिर काष्ठा snd_pci_quirk m3_amp_quirk_list[] = अणु
	SND_PCI_QUIRK(0x0E11, 0x0094, "Compaq Evo N600c", 0x0c),
	SND_PCI_QUIRK(0x10f7, 0x833e, "Panasonic CF-28", 0x0d),
	SND_PCI_QUIRK(0x10f7, 0x833d, "Panasonic CF-72", 0x0d),
	SND_PCI_QUIRK(0x1033, 0x80f1, "NEC LM800J/7", 0x03),
	SND_PCI_QUIRK(0x1509, 0x1740, "LEGEND ZhaoYang 3100CF", 0x03),
	अणु पूर्ण /* END */
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk m3_irda_quirk_list[] = अणु
	SND_PCI_QUIRK(0x1028, 0x00b0, "Dell Inspiron 4000", 1),
	SND_PCI_QUIRK(0x1028, 0x00a4, "Dell Inspiron 8000", 1),
	SND_PCI_QUIRK(0x1028, 0x00e6, "Dell Inspiron 8100", 1),
	अणु पूर्ण /* END */
पूर्ण;

/* hardware volume quirks */
अटल स्थिर काष्ठा snd_pci_quirk m3_hv_quirk_list[] = अणु
	/* Allegro chips */
	SND_PCI_QUIRK(0x0E11, 0x002E, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x0E11, 0x0094, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x0E11, 0xB112, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x0E11, 0xB114, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x103C, 0x0012, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x103C, 0x0018, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x103C, 0x001C, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x103C, 0x001D, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x103C, 0x001E, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x107B, 0x3350, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x10F7, 0x8338, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x10F7, 0x833C, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x10F7, 0x833D, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x10F7, 0x833E, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x10F7, 0x833F, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x13BD, 0x1018, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x13BD, 0x1019, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x13BD, 0x101A, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x14FF, 0x0F03, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x14FF, 0x0F04, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x14FF, 0x0F05, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x156D, 0xB400, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x156D, 0xB795, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x156D, 0xB797, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x156D, 0xC700, शून्य, HV_CTRL_ENABLE | HV_BUTTON_FROM_GD),
	SND_PCI_QUIRK(0x1033, 0x80F1, शून्य,
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x103C, 0x001A, शून्य, /* HP OmniBook 6100 */
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x107B, 0x340A, शून्य,
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x107B, 0x3450, शून्य,
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x109F, 0x3134, शून्य,
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x109F, 0x3161, शून्य,
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x144D, 0x3280, शून्य,
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x144D, 0x3281, शून्य,
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x144D, 0xC002, शून्य,
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x144D, 0xC003, शून्य,
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x1509, 0x1740, शून्य,
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x1610, 0x0010, शून्य,
		      HV_CTRL_ENABLE | HV_BUTTON_FROM_GD | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x1042, 0x1042, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x107B, 0x9500, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x14FF, 0x0F06, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x1558, 0x8586, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x161F, 0x2011, शून्य, HV_CTRL_ENABLE),
	/* Maestro3 chips */
	SND_PCI_QUIRK(0x103C, 0x000E, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x103C, 0x0010, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x103C, 0x0011, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x103C, 0x001B, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x104D, 0x80A6, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x104D, 0x80AA, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x107B, 0x5300, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x110A, 0x1998, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x13BD, 0x1015, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x13BD, 0x101C, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x13BD, 0x1802, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x1599, 0x0715, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x5643, 0x5643, शून्य, HV_CTRL_ENABLE),
	SND_PCI_QUIRK(0x144D, 0x3260, शून्य, HV_CTRL_ENABLE | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x144D, 0x3261, शून्य, HV_CTRL_ENABLE | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x144D, 0xC000, शून्य, HV_CTRL_ENABLE | REDUCED_DEBOUNCE),
	SND_PCI_QUIRK(0x144D, 0xC001, शून्य, HV_CTRL_ENABLE | REDUCED_DEBOUNCE),
	अणु पूर्ण /* END */
पूर्ण;

/* HP Omnibook quirks */
अटल स्थिर काष्ठा snd_pci_quirk m3_omnibook_quirk_list[] = अणु
	SND_PCI_QUIRK_ID(0x103c, 0x0010), /* HP OmniBook 6000 */
	SND_PCI_QUIRK_ID(0x103c, 0x0011), /* HP OmniBook 500 */
	अणु पूर्ण /* END */
पूर्ण;

/*
 * lowlevel functions
 */

अटल अंतरभूत व्योम snd_m3_outw(काष्ठा snd_m3 *chip, u16 value, अचिन्हित दीर्घ reg)
अणु
	outw(value, chip->iobase + reg);
पूर्ण

अटल अंतरभूत u16 snd_m3_inw(काष्ठा snd_m3 *chip, अचिन्हित दीर्घ reg)
अणु
	वापस inw(chip->iobase + reg);
पूर्ण

अटल अंतरभूत व्योम snd_m3_outb(काष्ठा snd_m3 *chip, u8 value, अचिन्हित दीर्घ reg)
अणु
	outb(value, chip->iobase + reg);
पूर्ण

अटल अंतरभूत u8 snd_m3_inb(काष्ठा snd_m3 *chip, अचिन्हित दीर्घ reg)
अणु
	वापस inb(chip->iobase + reg);
पूर्ण

/*
 * access 16bit words to the code or data regions of the dsp's memory.
 * index addresses 16bit words.
 */
अटल u16 snd_m3_assp_पढ़ो(काष्ठा snd_m3 *chip, u16 region, u16 index)
अणु
	snd_m3_outw(chip, region & MEMTYPE_MASK, DSP_PORT_MEMORY_TYPE);
	snd_m3_outw(chip, index, DSP_PORT_MEMORY_INDEX);
	वापस snd_m3_inw(chip, DSP_PORT_MEMORY_DATA);
पूर्ण

अटल व्योम snd_m3_assp_ग_लिखो(काष्ठा snd_m3 *chip, u16 region, u16 index, u16 data)
अणु
	snd_m3_outw(chip, region & MEMTYPE_MASK, DSP_PORT_MEMORY_TYPE);
	snd_m3_outw(chip, index, DSP_PORT_MEMORY_INDEX);
	snd_m3_outw(chip, data, DSP_PORT_MEMORY_DATA);
पूर्ण

अटल व्योम snd_m3_assp_halt(काष्ठा snd_m3 *chip)
अणु
	chip->reset_state = snd_m3_inb(chip, DSP_PORT_CONTROL_REG_B) & ~REGB_STOP_CLOCK;
	msleep(10);
	snd_m3_outb(chip, chip->reset_state & ~REGB_ENABLE_RESET, DSP_PORT_CONTROL_REG_B);
पूर्ण

अटल व्योम snd_m3_assp_जारी(काष्ठा snd_m3 *chip)
अणु
	snd_m3_outb(chip, chip->reset_state | REGB_ENABLE_RESET, DSP_PORT_CONTROL_REG_B);
पूर्ण


/*
 * This makes me sad. the maestro3 has lists
 * पूर्णांकernally that must be packed.. 0 terminates,
 * apparently, or maybe all unused entries have
 * to be 0, the lists have अटल lengths set
 * by the binary code images.
 */

अटल पूर्णांक snd_m3_add_list(काष्ठा snd_m3 *chip, काष्ठा m3_list *list, u16 val)
अणु
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  list->mem_addr + list->curlen,
			  val);
	वापस list->curlen++;
पूर्ण

अटल व्योम snd_m3_हटाओ_list(काष्ठा snd_m3 *chip, काष्ठा m3_list *list, पूर्णांक index)
अणु
	u16  val;
	पूर्णांक lastindex = list->curlen - 1;

	अगर (index != lastindex) अणु
		val = snd_m3_assp_पढ़ो(chip, MEMTYPE_INTERNAL_DATA,
				       list->mem_addr + lastindex);
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
				  list->mem_addr + index,
				  val);
	पूर्ण

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  list->mem_addr + lastindex,
			  0);

	list->curlen--;
पूर्ण

अटल व्योम snd_m3_inc_समयr_users(काष्ठा snd_m3 *chip)
अणु
	chip->समयr_users++;
	अगर (chip->समयr_users != 1) 
		वापस;

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_TIMER_COUNT_RELOAD,
			  240);

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_TIMER_COUNT_CURRENT,
			  240);

	snd_m3_outw(chip,
		    snd_m3_inw(chip, HOST_INT_CTRL) | CLKRUN_GEN_ENABLE,
		    HOST_INT_CTRL);
पूर्ण

अटल व्योम snd_m3_dec_समयr_users(काष्ठा snd_m3 *chip)
अणु
	chip->समयr_users--;
	अगर (chip->समयr_users > 0)  
		वापस;

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_TIMER_COUNT_RELOAD,
			  0);

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_TIMER_COUNT_CURRENT,
			  0);

	snd_m3_outw(chip,
		    snd_m3_inw(chip, HOST_INT_CTRL) & ~CLKRUN_GEN_ENABLE,
		    HOST_INT_CTRL);
पूर्ण

/*
 * start/stop
 */

/* spinlock held! */
अटल पूर्णांक snd_m3_pcm_start(काष्ठा snd_m3 *chip, काष्ठा m3_dma *s,
			    काष्ठा snd_pcm_substream *subs)
अणु
	अगर (! s || ! subs)
		वापस -EINVAL;

	snd_m3_inc_समयr_users(chip);
	चयन (subs->stream) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		chip->dacs_active++;
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
				  s->inst.data + CDATA_INSTANCE_READY, 1);
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
				  KDATA_MIXER_TASK_NUMBER,
				  chip->dacs_active);
		अवरोध;
	हाल SNDRV_PCM_STREAM_CAPTURE:
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
				  KDATA_ADC1_REQUEST, 1);
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
				  s->inst.data + CDATA_INSTANCE_READY, 1);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* spinlock held! */
अटल पूर्णांक snd_m3_pcm_stop(काष्ठा snd_m3 *chip, काष्ठा m3_dma *s,
			   काष्ठा snd_pcm_substream *subs)
अणु
	अगर (! s || ! subs)
		वापस -EINVAL;

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_INSTANCE_READY, 0);
	snd_m3_dec_समयr_users(chip);
	चयन (subs->stream) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		chip->dacs_active--;
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
				  KDATA_MIXER_TASK_NUMBER, 
				  chip->dacs_active);
		अवरोध;
	हाल SNDRV_PCM_STREAM_CAPTURE:
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
				  KDATA_ADC1_REQUEST, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_m3_pcm_trigger(काष्ठा snd_pcm_substream *subs, पूर्णांक cmd)
अणु
	काष्ठा snd_m3 *chip = snd_pcm_substream_chip(subs);
	काष्ठा m3_dma *s = subs->runसमय->निजी_data;
	पूर्णांक err = -EINVAL;

	अगर (snd_BUG_ON(!s))
		वापस -ENXIO;

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (s->running)
			err = -EBUSY;
		अन्यथा अणु
			s->running = 1;
			err = snd_m3_pcm_start(chip, s, subs);
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (! s->running)
			err = 0; /* should वापस error? */
		अन्यथा अणु
			s->running = 0;
			err = snd_m3_pcm_stop(chip, s, subs);
		पूर्ण
		अवरोध;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस err;
पूर्ण

/*
 * setup
 */
अटल व्योम 
snd_m3_pcm_setup1(काष्ठा snd_m3 *chip, काष्ठा m3_dma *s, काष्ठा snd_pcm_substream *subs)
अणु
	पूर्णांक dsp_in_size, dsp_out_size, dsp_in_buffer, dsp_out_buffer;
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;

	अगर (subs->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		dsp_in_size = MINISRC_IN_BUFFER_SIZE - (0x20 * 2);
		dsp_out_size = MINISRC_OUT_BUFFER_SIZE - (0x20 * 2);
	पूर्ण अन्यथा अणु
		dsp_in_size = MINISRC_IN_BUFFER_SIZE - (0x10 * 2);
		dsp_out_size = MINISRC_OUT_BUFFER_SIZE - (0x10 * 2);
	पूर्ण
	dsp_in_buffer = s->inst.data + (MINISRC_TMP_BUFFER_SIZE / 2);
	dsp_out_buffer = dsp_in_buffer + (dsp_in_size / 2) + 1;

	s->dma_size = frames_to_bytes(runसमय, runसमय->buffer_size);
	s->period_size = frames_to_bytes(runसमय, runसमय->period_size);
	s->hwptr = 0;
	s->count = 0;

#घोषणा LO(x) ((x) & 0xffff)
#घोषणा HI(x) LO((x) >> 16)

	/* host dma buffer poपूर्णांकers */
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_HOST_SRC_ADDRL,
			  LO(s->buffer_addr));

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_HOST_SRC_ADDRH,
			  HI(s->buffer_addr));

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_HOST_SRC_END_PLUS_1L,
			  LO(s->buffer_addr + s->dma_size));

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_HOST_SRC_END_PLUS_1H,
			  HI(s->buffer_addr + s->dma_size));

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_HOST_SRC_CURRENTL,
			  LO(s->buffer_addr));

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_HOST_SRC_CURRENTH,
			  HI(s->buffer_addr));
#अघोषित LO
#अघोषित HI

	/* dsp buffers */

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_IN_BUF_BEGIN,
			  dsp_in_buffer);

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_IN_BUF_END_PLUS_1,
			  dsp_in_buffer + (dsp_in_size / 2));

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_IN_BUF_HEAD,
			  dsp_in_buffer);
    
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_IN_BUF_TAIL,
			  dsp_in_buffer);

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_OUT_BUF_BEGIN,
			  dsp_out_buffer);

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_OUT_BUF_END_PLUS_1,
			  dsp_out_buffer + (dsp_out_size / 2));

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_OUT_BUF_HEAD,
			  dsp_out_buffer);

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_OUT_BUF_TAIL,
			  dsp_out_buffer);
पूर्ण

अटल व्योम snd_m3_pcm_setup2(काष्ठा snd_m3 *chip, काष्ठा m3_dma *s,
			      काष्ठा snd_pcm_runसमय *runसमय)
अणु
	u32 freq;

	/* 
	 * put us in the lists अगर we're not alपढ़ोy there
	 */
	अगर (! s->in_lists) अणु
		s->index[0] = snd_m3_add_list(chip, s->index_list[0],
					      s->inst.data >> DP_SHIFT_COUNT);
		s->index[1] = snd_m3_add_list(chip, s->index_list[1],
					      s->inst.data >> DP_SHIFT_COUNT);
		s->index[2] = snd_m3_add_list(chip, s->index_list[2],
					      s->inst.data >> DP_SHIFT_COUNT);
		s->in_lists = 1;
	पूर्ण

	/* ग_लिखो to 'mono' word */
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + SRC3_सूचीECTION_OFFSET + 1, 
			  runसमय->channels == 2 ? 0 : 1);
	/* ग_लिखो to '8bit' word */
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + SRC3_सूचीECTION_OFFSET + 2, 
			  snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16 ? 0 : 1);

	/* set up dac/adc rate */
	freq = DIV_ROUND_CLOSEST(runसमय->rate << 15, 48000);
	अगर (freq) 
		freq--;

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_FREQUENCY,
			  freq);
पूर्ण


अटल स्थिर काष्ठा play_vals अणु
	u16 addr, val;
पूर्ण pv[] = अणु
	अणुCDATA_LEFT_VOLUME, ARB_VOLUMEपूर्ण,
	अणुCDATA_RIGHT_VOLUME, ARB_VOLUMEपूर्ण,
	अणुSRC3_सूचीECTION_OFFSET, 0पूर्ण ,
	/* +1, +2 are stereo/16 bit */
	अणुSRC3_सूचीECTION_OFFSET + 3, 0x0000पूर्ण, /* fraction? */
	अणुSRC3_सूचीECTION_OFFSET + 4, 0पूर्ण, /* first l */
	अणुSRC3_सूचीECTION_OFFSET + 5, 0पूर्ण, /* first r */
	अणुSRC3_सूचीECTION_OFFSET + 6, 0पूर्ण, /* second l */
	अणुSRC3_सूचीECTION_OFFSET + 7, 0पूर्ण, /* second r */
	अणुSRC3_सूचीECTION_OFFSET + 8, 0पूर्ण, /* delta l */
	अणुSRC3_सूचीECTION_OFFSET + 9, 0पूर्ण, /* delta r */
	अणुSRC3_सूचीECTION_OFFSET + 10, 0x8000पूर्ण, /* round */
	अणुSRC3_सूचीECTION_OFFSET + 11, 0xFF00पूर्ण, /* higher bute mark */
	अणुSRC3_सूचीECTION_OFFSET + 13, 0पूर्ण, /* temp0 */
	अणुSRC3_सूचीECTION_OFFSET + 14, 0पूर्ण, /* c fraction */
	अणुSRC3_सूचीECTION_OFFSET + 15, 0पूर्ण, /* counter */
	अणुSRC3_सूचीECTION_OFFSET + 16, 8पूर्ण, /* numin */
	अणुSRC3_सूचीECTION_OFFSET + 17, 50*2पूर्ण, /* numout */
	अणुSRC3_सूचीECTION_OFFSET + 18, MINISRC_BIQUAD_STAGE - 1पूर्ण, /* numstage */
	अणुSRC3_सूचीECTION_OFFSET + 20, 0पूर्ण, /* filtertap */
	अणुSRC3_सूचीECTION_OFFSET + 21, 0पूर्ण /* booster */
पूर्ण;


/* the mode passed should be alपढ़ोy shअगरted and masked */
अटल व्योम
snd_m3_playback_setup(काष्ठा snd_m3 *chip, काष्ठा m3_dma *s,
		      काष्ठा snd_pcm_substream *subs)
अणु
	अचिन्हित पूर्णांक i;

	/*
	 * some per client initializers
	 */

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + SRC3_सूचीECTION_OFFSET + 12,
			  s->inst.data + 40 + 8);

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + SRC3_सूचीECTION_OFFSET + 19,
			  s->inst.code + MINISRC_COEF_LOC);

	/* enable or disable low pass filter? */
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + SRC3_सूचीECTION_OFFSET + 22,
			  subs->runसमय->rate > 45000 ? 0xff : 0);
    
	/* tell it which way dma is going? */
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_DMA_CONTROL,
			  DMACONTROL_AUTOREPEAT + DMAC_PAGE3_SELECTOR + DMAC_BLOCKF_SELECTOR);

	/*
	 * set an armload of अटल initializers
	 */
	क्रम (i = 0; i < ARRAY_SIZE(pv); i++) 
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
				  s->inst.data + pv[i].addr, pv[i].val);
पूर्ण

/*
 *    Native record driver 
 */
अटल स्थिर काष्ठा rec_vals अणु
	u16 addr, val;
पूर्ण rv[] = अणु
	अणुCDATA_LEFT_VOLUME, ARB_VOLUMEपूर्ण,
	अणुCDATA_RIGHT_VOLUME, ARB_VOLUMEपूर्ण,
	अणुSRC3_सूचीECTION_OFFSET, 1पूर्ण ,
	/* +1, +2 are stereo/16 bit */
	अणुSRC3_सूचीECTION_OFFSET + 3, 0x0000पूर्ण, /* fraction? */
	अणुSRC3_सूचीECTION_OFFSET + 4, 0पूर्ण, /* first l */
	अणुSRC3_सूचीECTION_OFFSET + 5, 0पूर्ण, /* first r */
	अणुSRC3_सूचीECTION_OFFSET + 6, 0पूर्ण, /* second l */
	अणुSRC3_सूचीECTION_OFFSET + 7, 0पूर्ण, /* second r */
	अणुSRC3_सूचीECTION_OFFSET + 8, 0पूर्ण, /* delta l */
	अणुSRC3_सूचीECTION_OFFSET + 9, 0पूर्ण, /* delta r */
	अणुSRC3_सूचीECTION_OFFSET + 10, 0x8000पूर्ण, /* round */
	अणुSRC3_सूचीECTION_OFFSET + 11, 0xFF00पूर्ण, /* higher bute mark */
	अणुSRC3_सूचीECTION_OFFSET + 13, 0पूर्ण, /* temp0 */
	अणुSRC3_सूचीECTION_OFFSET + 14, 0पूर्ण, /* c fraction */
	अणुSRC3_सूचीECTION_OFFSET + 15, 0पूर्ण, /* counter */
	अणुSRC3_सूचीECTION_OFFSET + 16, 50पूर्ण,/* numin */
	अणुSRC3_सूचीECTION_OFFSET + 17, 8पूर्ण, /* numout */
	अणुSRC3_सूचीECTION_OFFSET + 18, 0पूर्ण, /* numstage */
	अणुSRC3_सूचीECTION_OFFSET + 19, 0पूर्ण, /* coef */
	अणुSRC3_सूचीECTION_OFFSET + 20, 0पूर्ण, /* filtertap */
	अणुSRC3_सूचीECTION_OFFSET + 21, 0पूर्ण, /* booster */
	अणुSRC3_सूचीECTION_OFFSET + 22, 0xffपूर्ण /* skip lpf */
पूर्ण;

अटल व्योम
snd_m3_capture_setup(काष्ठा snd_m3 *chip, काष्ठा m3_dma *s, काष्ठा snd_pcm_substream *subs)
अणु
	अचिन्हित पूर्णांक i;

	/*
	 * some per client initializers
	 */

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + SRC3_सूचीECTION_OFFSET + 12,
			  s->inst.data + 40 + 8);

	/* tell it which way dma is going? */
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_DMA_CONTROL,
			  DMACONTROL_सूचीECTION + DMACONTROL_AUTOREPEAT + 
			  DMAC_PAGE3_SELECTOR + DMAC_BLOCKF_SELECTOR);

	/*
	 * set an armload of अटल initializers
	 */
	क्रम (i = 0; i < ARRAY_SIZE(rv); i++) 
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
				  s->inst.data + rv[i].addr, rv[i].val);
पूर्ण

अटल पूर्णांक snd_m3_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा m3_dma *s = substream->runसमय->निजी_data;

	/* set buffer address */
	s->buffer_addr = substream->runसमय->dma_addr;
	अगर (s->buffer_addr & 0x3) अणु
		dev_err(substream->pcm->card->dev, "oh my, not aligned\n");
		s->buffer_addr = s->buffer_addr & ~0x3;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_m3_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा m3_dma *s;
	
	अगर (substream->runसमय->निजी_data == शून्य)
		वापस 0;
	s = substream->runसमय->निजी_data;
	s->buffer_addr = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_m3_pcm_prepare(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_m3 *chip = snd_pcm_substream_chip(subs);
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा m3_dma *s = runसमय->निजी_data;

	अगर (snd_BUG_ON(!s))
		वापस -ENXIO;

	अगर (runसमय->क्रमmat != SNDRV_PCM_FORMAT_U8 &&
	    runसमय->क्रमmat != SNDRV_PCM_FORMAT_S16_LE)
		वापस -EINVAL;
	अगर (runसमय->rate > 48000 ||
	    runसमय->rate < 8000)
		वापस -EINVAL;

	spin_lock_irq(&chip->reg_lock);

	snd_m3_pcm_setup1(chip, s, subs);

	अगर (subs->stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_m3_playback_setup(chip, s, subs);
	अन्यथा
		snd_m3_capture_setup(chip, s, subs);

	snd_m3_pcm_setup2(chip, s, runसमय);

	spin_unlock_irq(&chip->reg_lock);

	वापस 0;
पूर्ण

/*
 * get current poपूर्णांकer
 */
अटल अचिन्हित पूर्णांक
snd_m3_get_poपूर्णांकer(काष्ठा snd_m3 *chip, काष्ठा m3_dma *s, काष्ठा snd_pcm_substream *subs)
अणु
	u16 hi = 0, lo = 0;
	पूर्णांक retry = 10;
	u32 addr;

	/*
	 * try and get a valid answer
	 */
	जबतक (retry--) अणु
		hi =  snd_m3_assp_पढ़ो(chip, MEMTYPE_INTERNAL_DATA,
				       s->inst.data + CDATA_HOST_SRC_CURRENTH);

		lo = snd_m3_assp_पढ़ो(chip, MEMTYPE_INTERNAL_DATA,
				      s->inst.data + CDATA_HOST_SRC_CURRENTL);

		अगर (hi == snd_m3_assp_पढ़ो(chip, MEMTYPE_INTERNAL_DATA,
					   s->inst.data + CDATA_HOST_SRC_CURRENTH))
			अवरोध;
	पूर्ण
	addr = lo | ((u32)hi<<16);
	वापस (अचिन्हित पूर्णांक)(addr - s->buffer_addr);
पूर्ण

अटल snd_pcm_uframes_t
snd_m3_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_m3 *chip = snd_pcm_substream_chip(subs);
	अचिन्हित पूर्णांक ptr;
	काष्ठा m3_dma *s = subs->runसमय->निजी_data;

	अगर (snd_BUG_ON(!s))
		वापस 0;

	spin_lock(&chip->reg_lock);
	ptr = snd_m3_get_poपूर्णांकer(chip, s, subs);
	spin_unlock(&chip->reg_lock);
	वापस bytes_to_frames(subs->runसमय, ptr);
पूर्ण


/* update poपूर्णांकer */
/* spinlock held! */
अटल व्योम snd_m3_update_ptr(काष्ठा snd_m3 *chip, काष्ठा m3_dma *s)
अणु
	काष्ठा snd_pcm_substream *subs = s->substream;
	अचिन्हित पूर्णांक hwptr;
	पूर्णांक dअगरf;

	अगर (! s->running)
		वापस;

	hwptr = snd_m3_get_poपूर्णांकer(chip, s, subs);

	/* try to aव्योम expensive modulo भागisions */
	अगर (hwptr >= s->dma_size)
		hwptr %= s->dma_size;

	dअगरf = s->dma_size + hwptr - s->hwptr;
	अगर (dअगरf >= s->dma_size)
		dअगरf %= s->dma_size;

	s->hwptr = hwptr;
	s->count += dअगरf;

	अगर (s->count >= (चिन्हित)s->period_size) अणु

		अगर (s->count < 2 * (चिन्हित)s->period_size)
			s->count -= (चिन्हित)s->period_size;
		अन्यथा
			s->count %= s->period_size;

		spin_unlock(&chip->reg_lock);
		snd_pcm_period_elapsed(subs);
		spin_lock(&chip->reg_lock);
	पूर्ण
पूर्ण

/* The m3's hardware volume works by incrementing / decrementing 2 counters
   (without wrap around) in response to volume button presses and then
   generating an पूर्णांकerrupt. The pair of counters is stored in bits 1-3 and 5-7
   of a byte wide रेजिस्टर. The meaning of bits 0 and 4 is unknown. */
अटल व्योम snd_m3_update_hw_volume(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_m3 *chip = container_of(work, काष्ठा snd_m3, hwvol_work);
	पूर्णांक x, val;

	/* Figure out which volume control button was pushed,
	   based on dअगरferences from the शेष रेजिस्टर
	   values. */
	x = inb(chip->iobase + SHADOW_MIX_REG_VOICE) & 0xee;

	/* Reset the volume counters to 4. Tests on the allegro पूर्णांकegrated
	   पूर्णांकo a Compaq N600C laptop, have revealed that:
	   1) Writing any value will result in the 2 counters being reset to
	      4 so writing 0x88 is not strictly necessary
	   2) Writing to any of the 4 involved रेजिस्टरs will reset all 4
	      of them (and पढ़ोing them always वापसs the same value क्रम all
	      of them)
	   It could be that a maestro deviates from this, so leave the code
	   as is. */
	outb(0x88, chip->iobase + SHADOW_MIX_REG_VOICE);
	outb(0x88, chip->iobase + HW_VOL_COUNTER_VOICE);
	outb(0x88, chip->iobase + SHADOW_MIX_REG_MASTER);
	outb(0x88, chip->iobase + HW_VOL_COUNTER_MASTER);

	/* Ignore spurious HV पूर्णांकerrupts during suspend / resume, this aव्योमs
	   mistaking them क्रम a mute button press. */
	अगर (chip->in_suspend)
		वापस;

#अगर_अघोषित CONFIG_SND_MAESTRO3_INPUT
	अगर (!chip->master_चयन || !chip->master_volume)
		वापस;

	val = snd_ac97_पढ़ो(chip->ac97, AC97_MASTER);
	चयन (x) अणु
	हाल 0x88:
		/* The counters have not changed, yet we've received a HV
		   पूर्णांकerrupt. According to tests run by various people this
		   happens when pressing the mute button. */
		val ^= 0x8000;
		अवरोध;
	हाल 0xaa:
		/* counters increased by 1 -> volume up */
		अगर ((val & 0x7f) > 0)
			val--;
		अगर ((val & 0x7f00) > 0)
			val -= 0x0100;
		अवरोध;
	हाल 0x66:
		/* counters decreased by 1 -> volume करोwn */
		अगर ((val & 0x7f) < 0x1f)
			val++;
		अगर ((val & 0x7f00) < 0x1f00)
			val += 0x0100;
		अवरोध;
	पूर्ण
	अगर (snd_ac97_update(chip->ac97, AC97_MASTER, val))
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->master_चयन->id);
#अन्यथा
	अगर (!chip->input_dev)
		वापस;

	val = 0;
	चयन (x) अणु
	हाल 0x88:
		/* The counters have not changed, yet we've received a HV
		   पूर्णांकerrupt. According to tests run by various people this
		   happens when pressing the mute button. */
		val = KEY_MUTE;
		अवरोध;
	हाल 0xaa:
		/* counters increased by 1 -> volume up */
		val = KEY_VOLUMEUP;
		अवरोध;
	हाल 0x66:
		/* counters decreased by 1 -> volume करोwn */
		val = KEY_VOLUMEDOWN;
		अवरोध;
	पूर्ण

	अगर (val) अणु
		input_report_key(chip->input_dev, val, 1);
		input_sync(chip->input_dev);
		input_report_key(chip->input_dev, val, 0);
		input_sync(chip->input_dev);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल irqवापस_t snd_m3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_m3 *chip = dev_id;
	u8 status;
	पूर्णांक i;

	status = inb(chip->iobase + HOST_INT_STATUS);

	अगर (status == 0xff)
		वापस IRQ_NONE;

	अगर (status & HV_INT_PENDING)
		schedule_work(&chip->hwvol_work);

	/*
	 * ack an assp पूर्णांक अगर its running
	 * and has an पूर्णांक pending
	 */
	अगर (status & ASSP_INT_PENDING) अणु
		u8 ctl = inb(chip->iobase + ASSP_CONTROL_B);
		अगर (!(ctl & STOP_ASSP_CLOCK)) अणु
			ctl = inb(chip->iobase + ASSP_HOST_INT_STATUS);
			अगर (ctl & DSP2HOST_REQ_TIMER) अणु
				outb(DSP2HOST_REQ_TIMER, chip->iobase + ASSP_HOST_INT_STATUS);
				/* update adc/dac info अगर it was a समयr पूर्णांक */
				spin_lock(&chip->reg_lock);
				क्रम (i = 0; i < chip->num_substreams; i++) अणु
					काष्ठा m3_dma *s = &chip->substreams[i];
					अगर (s->running)
						snd_m3_update_ptr(chip, s);
				पूर्ण
				spin_unlock(&chip->reg_lock);
			पूर्ण
		पूर्ण
	पूर्ण

#अगर 0 /* TODO: not supported yet */
	अगर ((status & MPU401_INT_PENDING) && chip->rmidi)
		snd_mpu401_uart_पूर्णांकerrupt(irq, chip->rmidi->निजी_data, regs);
#पूर्ण_अगर

	/* ack पूर्णांकs */
	outb(status, chip->iobase + HOST_INT_STATUS);

	वापस IRQ_HANDLED;
पूर्ण


/*
 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_m3_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 /*SNDRV_PCM_INFO_PAUSE |*/
				 SNDRV_PCM_INFO_RESUME),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		8000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(512*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(512*1024),
	.periods_min =		1,
	.periods_max =		1024,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_m3_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 /*SNDRV_PCM_INFO_PAUSE |*/
				 SNDRV_PCM_INFO_RESUME),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		8000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(512*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(512*1024),
	.periods_min =		1,
	.periods_max =		1024,
पूर्ण;


/*
 */

अटल पूर्णांक
snd_m3_substream_खोलो(काष्ठा snd_m3 *chip, काष्ठा snd_pcm_substream *subs)
अणु
	पूर्णांक i;
	काष्ठा m3_dma *s;

	spin_lock_irq(&chip->reg_lock);
	क्रम (i = 0; i < chip->num_substreams; i++) अणु
		s = &chip->substreams[i];
		अगर (! s->खोलोed)
			जाओ __found;
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);
	वापस -ENOMEM;
__found:
	s->खोलोed = 1;
	s->running = 0;
	spin_unlock_irq(&chip->reg_lock);

	subs->runसमय->निजी_data = s;
	s->substream = subs;

	/* set list owners */
	अगर (subs->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		s->index_list[0] = &chip->mixer_list;
	पूर्ण अन्यथा
		s->index_list[0] = &chip->adc1_list;
	s->index_list[1] = &chip->msrc_list;
	s->index_list[2] = &chip->dma_list;

	वापस 0;
पूर्ण

अटल व्योम
snd_m3_substream_बंद(काष्ठा snd_m3 *chip, काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा m3_dma *s = subs->runसमय->निजी_data;

	अगर (s == शून्य)
		वापस; /* not खोलोed properly */

	spin_lock_irq(&chip->reg_lock);
	अगर (s->substream && s->running)
		snd_m3_pcm_stop(chip, s, s->substream); /* करोes this happen? */
	अगर (s->in_lists) अणु
		snd_m3_हटाओ_list(chip, s->index_list[0], s->index[0]);
		snd_m3_हटाओ_list(chip, s->index_list[1], s->index[1]);
		snd_m3_हटाओ_list(chip, s->index_list[2], s->index[2]);
		s->in_lists = 0;
	पूर्ण
	s->running = 0;
	s->खोलोed = 0;
	spin_unlock_irq(&chip->reg_lock);
पूर्ण

अटल पूर्णांक
snd_m3_playback_खोलो(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_m3 *chip = snd_pcm_substream_chip(subs);
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	पूर्णांक err;

	अगर ((err = snd_m3_substream_खोलो(chip, subs)) < 0)
		वापस err;

	runसमय->hw = snd_m3_playback;

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_m3_playback_बंद(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_m3 *chip = snd_pcm_substream_chip(subs);

	snd_m3_substream_बंद(chip, subs);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_m3_capture_खोलो(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_m3 *chip = snd_pcm_substream_chip(subs);
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	पूर्णांक err;

	अगर ((err = snd_m3_substream_खोलो(chip, subs)) < 0)
		वापस err;

	runसमय->hw = snd_m3_capture;

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_m3_capture_बंद(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_m3 *chip = snd_pcm_substream_chip(subs);

	snd_m3_substream_बंद(chip, subs);
	वापस 0;
पूर्ण

/*
 * create pcm instance
 */

अटल स्थिर काष्ठा snd_pcm_ops snd_m3_playback_ops = अणु
	.खोलो =		snd_m3_playback_खोलो,
	.बंद =	snd_m3_playback_बंद,
	.hw_params =	snd_m3_pcm_hw_params,
	.hw_मुक्त =	snd_m3_pcm_hw_मुक्त,
	.prepare =	snd_m3_pcm_prepare,
	.trigger =	snd_m3_pcm_trigger,
	.poपूर्णांकer =	snd_m3_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_m3_capture_ops = अणु
	.खोलो =		snd_m3_capture_खोलो,
	.बंद =	snd_m3_capture_बंद,
	.hw_params =	snd_m3_pcm_hw_params,
	.hw_मुक्त =	snd_m3_pcm_hw_मुक्त,
	.prepare =	snd_m3_pcm_prepare,
	.trigger =	snd_m3_pcm_trigger,
	.poपूर्णांकer =	snd_m3_pcm_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक
snd_m3_pcm(काष्ठा snd_m3 * chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(chip->card, chip->card->driver, device,
			  MAX_PLAYBACKS, MAX_CAPTURES, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_m3_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_m3_capture_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	म_नकल(pcm->name, chip->card->driver);
	chip->pcm = pcm;
	
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev, 64*1024, 64*1024);

	वापस 0;
पूर्ण


/*
 * ac97 पूर्णांकerface
 */

/*
 * Wait क्रम the ac97 serial bus to be मुक्त.
 * वापस nonzero अगर the bus is still busy.
 */
अटल पूर्णांक snd_m3_ac97_रुको(काष्ठा snd_m3 *chip)
अणु
	पूर्णांक i = 10000;

	करो अणु
		अगर (! (snd_m3_inb(chip, 0x30) & 1))
			वापस 0;
		cpu_relax();
	पूर्ण जबतक (i-- > 0);

	dev_err(chip->card->dev, "ac97 serial bus busy\n");
	वापस 1;
पूर्ण

अटल अचिन्हित लघु
snd_m3_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	काष्ठा snd_m3 *chip = ac97->निजी_data;
	अचिन्हित लघु data = 0xffff;

	अगर (snd_m3_ac97_रुको(chip))
		जाओ fail;
	snd_m3_outb(chip, 0x80 | (reg & 0x7f), CODEC_COMMAND);
	अगर (snd_m3_ac97_रुको(chip))
		जाओ fail;
	data = snd_m3_inw(chip, CODEC_DATA);
fail:
	वापस data;
पूर्ण

अटल व्योम
snd_m3_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	काष्ठा snd_m3 *chip = ac97->निजी_data;

	अगर (snd_m3_ac97_रुको(chip))
		वापस;
	snd_m3_outw(chip, val, CODEC_DATA);
	snd_m3_outb(chip, reg & 0x7f, CODEC_COMMAND);
	/*
	 * Workaround क्रम buggy ES1988 पूर्णांकegrated AC'97 codec. It reमुख्यs silent
	 * until the MASTER volume or mute is touched (alsactl restore करोes not
	 * work).
	 */
	अगर (ac97->id == 0x45838308 && reg == AC97_MASTER) अणु
		snd_m3_ac97_रुको(chip);
		snd_m3_outw(chip, val, CODEC_DATA);
		snd_m3_outb(chip, reg & 0x7f, CODEC_COMMAND);
	पूर्ण
पूर्ण


अटल व्योम snd_m3_remote_codec_config(काष्ठा snd_m3 *chip, पूर्णांक isremote)
अणु
	पूर्णांक io = chip->iobase;
	u16 पंचांगp;

	isremote = isremote ? 1 : 0;

	पंचांगp = inw(io + RING_BUS_CTRL_B) & ~SECOND_CODEC_ID_MASK;
	/* enable करोck on Dell Latitude C810 */
	अगर (chip->pci->subप्रणाली_venकरोr == 0x1028 &&
	    chip->pci->subप्रणाली_device == 0x00e5)
		पंचांगp |= M3I_DOCK_ENABLE;
	outw(पंचांगp | isremote, io + RING_BUS_CTRL_B);
	outw((inw(io + SDO_OUT_DEST_CTRL) & ~COMMAND_ADDR_OUT) | isremote,
	     io + SDO_OUT_DEST_CTRL);
	outw((inw(io + SDO_IN_DEST_CTRL) & ~STATUS_ADDR_IN) | isremote,
	     io + SDO_IN_DEST_CTRL);
पूर्ण

/* 
 * hack, वापसs non zero on err 
 */
अटल पूर्णांक snd_m3_try_पढ़ो_venकरोr(काष्ठा snd_m3 *chip)
अणु
	u16 ret;

	अगर (snd_m3_ac97_रुको(chip))
		वापस 1;

	snd_m3_outb(chip, 0x80 | (AC97_VENDOR_ID1 & 0x7f), 0x30);

	अगर (snd_m3_ac97_रुको(chip))
		वापस 1;

	ret = snd_m3_inw(chip, 0x32);

	वापस (ret == 0) || (ret == 0xffff);
पूर्ण

अटल व्योम snd_m3_ac97_reset(काष्ठा snd_m3 *chip)
अणु
	u16 dir;
	पूर्णांक delay1 = 0, delay2 = 0, i;
	पूर्णांक io = chip->iobase;

	अगर (chip->allegro_flag) अणु
		/*
		 * the onboard codec on the allegro seems 
		 * to want to रुको a very दीर्घ समय beक्रमe
		 * coming back to lअगरe 
		 */
		delay1 = 50;
		delay2 = 800;
	पूर्ण अन्यथा अणु
		/* maestro3 */
		delay1 = 20;
		delay2 = 500;
	पूर्ण

	क्रम (i = 0; i < 5; i++) अणु
		dir = inw(io + GPIO_सूचीECTION);
		अगर (!chip->irda_workaround)
			dir |= 0x10; /* assuming pci bus master? */

		snd_m3_remote_codec_config(chip, 0);

		outw(IO_SRAM_ENABLE, io + RING_BUS_CTRL_A);
		udelay(20);

		outw(dir & ~GPO_PRIMARY_AC97 , io + GPIO_सूचीECTION);
		outw(~GPO_PRIMARY_AC97 , io + GPIO_MASK);
		outw(0, io + GPIO_DATA);
		outw(dir | GPO_PRIMARY_AC97, io + GPIO_सूचीECTION);

		schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(delay1));

		outw(GPO_PRIMARY_AC97, io + GPIO_DATA);
		udelay(5);
		/* ok, bring back the ac-link */
		outw(IO_SRAM_ENABLE | SERIAL_AC_LINK_ENABLE, io + RING_BUS_CTRL_A);
		outw(~0, io + GPIO_MASK);

		schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(delay2));

		अगर (! snd_m3_try_पढ़ो_venकरोr(chip))
			अवरोध;

		delay1 += 10;
		delay2 += 100;

		dev_dbg(chip->card->dev,
			"retrying codec reset with delays of %d and %d ms\n",
			   delay1, delay2);
	पूर्ण

#अगर 0
	/* more gung-ho reset that करोesn't
	 * seem to work anywhere :)
	 */
	पंचांगp = inw(io + RING_BUS_CTRL_A);
	outw(RAC_SDFS_ENABLE|LAC_SDFS_ENABLE, io + RING_BUS_CTRL_A);
	msleep(20);
	outw(पंचांगp, io + RING_BUS_CTRL_A);
	msleep(50);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक snd_m3_mixer(काष्ठा snd_m3 *chip)
अणु
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
#अगर_अघोषित CONFIG_SND_MAESTRO3_INPUT
	काष्ठा snd_ctl_elem_id elem_id;
#पूर्ण_अगर
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_m3_ac97_ग_लिखो,
		.पढ़ो = snd_m3_ac97_पढ़ो,
	पूर्ण;

	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, शून्य, &pbus)) < 0)
		वापस err;
	
	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	अगर ((err = snd_ac97_mixer(pbus, &ac97, &chip->ac97)) < 0)
		वापस err;

	/* seems ac97 PCM needs initialization.. hack hack.. */
	snd_ac97_ग_लिखो(chip->ac97, AC97_PCM, 0x8000 | (15 << 8) | 15);
	schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(100));
	snd_ac97_ग_लिखो(chip->ac97, AC97_PCM, 0);

#अगर_अघोषित CONFIG_SND_MAESTRO3_INPUT
	स_रखो(&elem_id, 0, माप(elem_id));
	elem_id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(elem_id.name, "Master Playback Switch");
	chip->master_चयन = snd_ctl_find_id(chip->card, &elem_id);
	स_रखो(&elem_id, 0, माप(elem_id));
	elem_id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(elem_id.name, "Master Playback Volume");
	chip->master_volume = snd_ctl_find_id(chip->card, &elem_id);
#पूर्ण_अगर

	वापस 0;
पूर्ण


/*
 * initialize ASSP
 */

#घोषणा MINISRC_LPF_LEN 10
अटल स्थिर u16 minisrc_lpf[MINISRC_LPF_LEN] = अणु
	0X0743, 0X1104, 0X0A4C, 0XF88D, 0X242C,
	0X1023, 0X1AA9, 0X0B60, 0XEFDD, 0X186F
पूर्ण;

अटल व्योम snd_m3_assp_init(काष्ठा snd_m3 *chip)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर __le16 *data;

	/* zero kernel data */
	क्रम (i = 0; i < (REV_B_DATA_MEMORY_UNIT_LENGTH * NUM_UNITS_KERNEL_DATA) / 2; i++)
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA, 
				  KDATA_BASE_ADDR + i, 0);

	/* zero mixer data? */
	क्रम (i = 0; i < (REV_B_DATA_MEMORY_UNIT_LENGTH * NUM_UNITS_KERNEL_DATA) / 2; i++)
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
				  KDATA_BASE_ADDR2 + i, 0);

	/* init dma poपूर्णांकer */
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_CURRENT_DMA,
			  KDATA_DMA_XFER0);

	/* ग_लिखो kernel पूर्णांकo code memory.. */
	data = (स्थिर __le16 *)chip->assp_kernel_image->data;
	क्रम (i = 0 ; i * 2 < chip->assp_kernel_image->size; i++) अणु
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_CODE, 
				  REV_B_CODE_MEMORY_BEGIN + i,
				  le16_to_cpu(data[i]));
	पूर्ण

	/*
	 * We only have this one client and we know that 0x400
	 * is मुक्त in our kernel's mem map, so lets just
	 * drop it there.  It seems that the minisrc करोesn't
	 * need vectors, so we won't bother with them..
	 */
	data = (स्थिर __le16 *)chip->assp_minisrc_image->data;
	क्रम (i = 0; i * 2 < chip->assp_minisrc_image->size; i++) अणु
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_CODE, 
				  0x400 + i, le16_to_cpu(data[i]));
	पूर्ण

	/*
	 * ग_लिखो the coefficients क्रम the low pass filter?
	 */
	क्रम (i = 0; i < MINISRC_LPF_LEN ; i++) अणु
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_CODE,
				  0x400 + MINISRC_COEF_LOC + i,
				  minisrc_lpf[i]);
	पूर्ण

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_CODE,
			  0x400 + MINISRC_COEF_LOC + MINISRC_LPF_LEN,
			  0x8000);

	/*
	 * the minisrc is the only thing on
	 * our task list..
	 */
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA, 
			  KDATA_TASK0,
			  0x400);

	/*
	 * init the mixer number..
	 */

	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_MIXER_TASK_NUMBER,0);

	/*
	 * EXTREME KERNEL MASTER VOLUME
	 */
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_DAC_LEFT_VOLUME, ARB_VOLUME);
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_DAC_RIGHT_VOLUME, ARB_VOLUME);

	chip->mixer_list.curlen = 0;
	chip->mixer_list.mem_addr = KDATA_MIXER_XFER0;
	chip->mixer_list.max = MAX_VIRTUAL_MIXER_CHANNELS;
	chip->adc1_list.curlen = 0;
	chip->adc1_list.mem_addr = KDATA_ADC1_XFER0;
	chip->adc1_list.max = MAX_VIRTUAL_ADC1_CHANNELS;
	chip->dma_list.curlen = 0;
	chip->dma_list.mem_addr = KDATA_DMA_XFER0;
	chip->dma_list.max = MAX_VIRTUAL_DMA_CHANNELS;
	chip->msrc_list.curlen = 0;
	chip->msrc_list.mem_addr = KDATA_INSTANCE0_MINISRC;
	chip->msrc_list.max = MAX_INSTANCE_MINISRC;
पूर्ण


अटल पूर्णांक snd_m3_assp_client_init(काष्ठा snd_m3 *chip, काष्ठा m3_dma *s, पूर्णांक index)
अणु
	पूर्णांक data_bytes = 2 * ( MINISRC_TMP_BUFFER_SIZE / 2 + 
			       MINISRC_IN_BUFFER_SIZE / 2 +
			       1 + MINISRC_OUT_BUFFER_SIZE / 2 + 1 );
	पूर्णांक address, i;

	/*
	 * the revb memory map has 0x1100 through 0x1c00
	 * मुक्त.  
	 */

	/*
	 * align instance address to 256 bytes so that its
	 * shअगरted list address is aligned.
	 * list address = (mem address >> 1) >> 7;
	 */
	data_bytes = ALIGN(data_bytes, 256);
	address = 0x1100 + ((data_bytes/2) * index);

	अगर ((address + (data_bytes/2)) >= 0x1c00) अणु
		dev_err(chip->card->dev,
			"no memory for %d bytes at ind %d (addr 0x%x)\n",
			   data_bytes, index, address);
		वापस -ENOMEM;
	पूर्ण

	s->number = index;
	s->inst.code = 0x400;
	s->inst.data = address;

	क्रम (i = data_bytes / 2; i > 0; address++, i--) अणु
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA,
				  address, 0);
	पूर्ण

	वापस 0;
पूर्ण


/* 
 * this works क्रम the reference board, have to find
 * out about others
 *
 * this needs more magic क्रम 4 speaker, but..
 */
अटल व्योम
snd_m3_amp_enable(काष्ठा snd_m3 *chip, पूर्णांक enable)
अणु
	पूर्णांक io = chip->iobase;
	u16 gpo, polarity;

	अगर (! chip->बाह्यal_amp)
		वापस;

	polarity = enable ? 0 : 1;
	polarity = polarity << chip->amp_gpio;
	gpo = 1 << chip->amp_gpio;

	outw(~gpo, io + GPIO_MASK);

	outw(inw(io + GPIO_सूचीECTION) | gpo,
	     io + GPIO_सूचीECTION);

	outw((GPO_SECONDARY_AC97 | GPO_PRIMARY_AC97 | polarity),
	     io + GPIO_DATA);

	outw(0xffff, io + GPIO_MASK);
पूर्ण

अटल व्योम
snd_m3_hv_init(काष्ठा snd_m3 *chip)
अणु
	अचिन्हित दीर्घ io = chip->iobase;
	u16 val = GPI_VOL_DOWN | GPI_VOL_UP;

	अगर (!chip->is_omnibook)
		वापस;

	/*
	 * Volume buttons on some HP OmniBook laptops
	 * require some GPIO magic to work correctly.
	 */
	outw(0xffff, io + GPIO_MASK);
	outw(0x0000, io + GPIO_DATA);

	outw(~val, io + GPIO_MASK);
	outw(inw(io + GPIO_सूचीECTION) & ~val, io + GPIO_सूचीECTION);
	outw(val, io + GPIO_MASK);

	outw(0xffff, io + GPIO_MASK);
पूर्ण

अटल पूर्णांक
snd_m3_chip_init(काष्ठा snd_m3 *chip)
अणु
	काष्ठा pci_dev *pcidev = chip->pci;
	अचिन्हित दीर्घ io = chip->iobase;
	u32 n;
	u16 w;
	u8 t; /* makes as much sense as 'n', no? */

	pci_पढ़ो_config_word(pcidev, PCI_LEGACY_AUDIO_CTRL, &w);
	w &= ~(SOUND_BLASTER_ENABLE|FM_SYNTHESIS_ENABLE|
	       MPU401_IO_ENABLE|MPU401_IRQ_ENABLE|ALIAS_10BIT_IO|
	       DISABLE_LEGACY);
	pci_ग_लिखो_config_word(pcidev, PCI_LEGACY_AUDIO_CTRL, w);

	pci_पढ़ो_config_dword(pcidev, PCI_ALLEGRO_CONFIG, &n);
	n &= ~(HV_CTRL_ENABLE | REDUCED_DEBOUNCE | HV_BUTTON_FROM_GD);
	n |= chip->hv_config;
	/* For some reason we must always use reduced debounce. */
	n |= REDUCED_DEBOUNCE;
	n |= PM_CTRL_ENABLE | CLK_DIV_BY_49 | USE_PCI_TIMING;
	pci_ग_लिखो_config_dword(pcidev, PCI_ALLEGRO_CONFIG, n);

	outb(RESET_ASSP, chip->iobase + ASSP_CONTROL_B);
	pci_पढ़ो_config_dword(pcidev, PCI_ALLEGRO_CONFIG, &n);
	n &= ~INT_CLK_SELECT;
	अगर (!chip->allegro_flag) अणु
		n &= ~INT_CLK_MULT_ENABLE; 
		n |= INT_CLK_SRC_NOT_PCI;
	पूर्ण
	n &=  ~( CLK_MULT_MODE_SELECT | CLK_MULT_MODE_SELECT_2 );
	pci_ग_लिखो_config_dword(pcidev, PCI_ALLEGRO_CONFIG, n);

	अगर (chip->allegro_flag) अणु
		pci_पढ़ो_config_dword(pcidev, PCI_USER_CONFIG, &n);
		n |= IN_CLK_12MHZ_SELECT;
		pci_ग_लिखो_config_dword(pcidev, PCI_USER_CONFIG, n);
	पूर्ण

	t = inb(chip->iobase + ASSP_CONTROL_A);
	t &= ~( DSP_CLK_36MHZ_SELECT  | ASSP_CLK_49MHZ_SELECT);
	t |= ASSP_CLK_49MHZ_SELECT;
	t |= ASSP_0_WS_ENABLE; 
	outb(t, chip->iobase + ASSP_CONTROL_A);

	snd_m3_assp_init(chip); /* करोwnload DSP code beक्रमe starting ASSP below */
	outb(RUN_ASSP, chip->iobase + ASSP_CONTROL_B); 

	outb(0x00, io + HARDWARE_VOL_CTRL);
	outb(0x88, io + SHADOW_MIX_REG_VOICE);
	outb(0x88, io + HW_VOL_COUNTER_VOICE);
	outb(0x88, io + SHADOW_MIX_REG_MASTER);
	outb(0x88, io + HW_VOL_COUNTER_MASTER);

	वापस 0;
पूर्ण 

अटल व्योम
snd_m3_enable_पूर्णांकs(काष्ठा snd_m3 *chip)
अणु
	अचिन्हित दीर्घ io = chip->iobase;
	अचिन्हित लघु val;

	/* TODO: MPU401 not supported yet */
	val = ASSP_INT_ENABLE /*| MPU401_INT_ENABLE*/;
	अगर (chip->hv_config & HV_CTRL_ENABLE)
		val |= HV_INT_ENABLE;
	outb(val, chip->iobase + HOST_INT_STATUS);
	outw(val, io + HOST_INT_CTRL);
	outb(inb(io + ASSP_CONTROL_C) | ASSP_HOST_INT_ENABLE,
	     io + ASSP_CONTROL_C);
पूर्ण


/*
 */

अटल पूर्णांक snd_m3_मुक्त(काष्ठा snd_m3 *chip)
अणु
	काष्ठा m3_dma *s;
	पूर्णांक i;

	cancel_work_sync(&chip->hwvol_work);
#अगर_घोषित CONFIG_SND_MAESTRO3_INPUT
	अगर (chip->input_dev)
		input_unरेजिस्टर_device(chip->input_dev);
#पूर्ण_अगर

	अगर (chip->substreams) अणु
		spin_lock_irq(&chip->reg_lock);
		क्रम (i = 0; i < chip->num_substreams; i++) अणु
			s = &chip->substreams[i];
			/* check surviving pcms; this should not happen though.. */
			अगर (s->substream && s->running)
				snd_m3_pcm_stop(chip, s, s->substream);
		पूर्ण
		spin_unlock_irq(&chip->reg_lock);
		kमुक्त(chip->substreams);
	पूर्ण
	अगर (chip->iobase) अणु
		outw(0, chip->iobase + HOST_INT_CTRL); /* disable पूर्णांकs */
	पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
	vमुक्त(chip->suspend_mem);
#पूर्ण_अगर

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);

	अगर (chip->iobase)
		pci_release_regions(chip->pci);

	release_firmware(chip->assp_kernel_image);
	release_firmware(chip->assp_minisrc_image);

	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण


/*
 * APM support
 */
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक m3_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_m3 *chip = card->निजी_data;
	पूर्णांक i, dsp_index;

	अगर (chip->suspend_mem == शून्य)
		वापस 0;

	chip->in_suspend = 1;
	cancel_work_sync(&chip->hwvol_work);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_ac97_suspend(chip->ac97);

	msleep(10); /* give the assp a chance to idle.. */

	snd_m3_assp_halt(chip);

	/* save dsp image */
	dsp_index = 0;
	क्रम (i = REV_B_CODE_MEMORY_BEGIN; i <= REV_B_CODE_MEMORY_END; i++)
		chip->suspend_mem[dsp_index++] =
			snd_m3_assp_पढ़ो(chip, MEMTYPE_INTERNAL_CODE, i);
	क्रम (i = REV_B_DATA_MEMORY_BEGIN ; i <= REV_B_DATA_MEMORY_END; i++)
		chip->suspend_mem[dsp_index++] =
			snd_m3_assp_पढ़ो(chip, MEMTYPE_INTERNAL_DATA, i);
	वापस 0;
पूर्ण

अटल पूर्णांक m3_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_m3 *chip = card->निजी_data;
	पूर्णांक i, dsp_index;

	अगर (chip->suspend_mem == शून्य)
		वापस 0;

	/* first lets just bring everything back. .*/
	snd_m3_outw(chip, 0, 0x54);
	snd_m3_outw(chip, 0, 0x56);

	snd_m3_chip_init(chip);
	snd_m3_assp_halt(chip);
	snd_m3_ac97_reset(chip);

	/* restore dsp image */
	dsp_index = 0;
	क्रम (i = REV_B_CODE_MEMORY_BEGIN; i <= REV_B_CODE_MEMORY_END; i++)
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_CODE, i, 
				  chip->suspend_mem[dsp_index++]);
	क्रम (i = REV_B_DATA_MEMORY_BEGIN ; i <= REV_B_DATA_MEMORY_END; i++)
		snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA, i, 
				  chip->suspend_mem[dsp_index++]);

	/* tell the dma engine to restart itself */
	snd_m3_assp_ग_लिखो(chip, MEMTYPE_INTERNAL_DATA, 
			  KDATA_DMA_ACTIVE, 0);

        /* restore ac97 रेजिस्टरs */
	snd_ac97_resume(chip->ac97);

	snd_m3_assp_जारी(chip);
	snd_m3_enable_पूर्णांकs(chip);
	snd_m3_amp_enable(chip, 1);

	snd_m3_hv_init(chip);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	chip->in_suspend = 0;
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(m3_pm, m3_suspend, m3_resume);
#घोषणा M3_PM_OPS	&m3_pm
#अन्यथा
#घोषणा M3_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_SND_MAESTRO3_INPUT
अटल पूर्णांक snd_m3_input_रेजिस्टर(काष्ठा snd_m3 *chip)
अणु
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	snम_लिखो(chip->phys, माप(chip->phys), "pci-%s/input0",
		 pci_name(chip->pci));

	input_dev->name = chip->card->driver;
	input_dev->phys = chip->phys;
	input_dev->id.bustype = BUS_PCI;
	input_dev->id.venकरोr  = chip->pci->venकरोr;
	input_dev->id.product = chip->pci->device;
	input_dev->dev.parent = &chip->pci->dev;

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(KEY_MUTE, input_dev->keybit);
	__set_bit(KEY_VOLUMEDOWN, input_dev->keybit);
	__set_bit(KEY_VOLUMEUP, input_dev->keybit);

	err = input_रेजिस्टर_device(input_dev);
	अगर (err) अणु
		input_मुक्त_device(input_dev);
		वापस err;
	पूर्ण

	chip->input_dev = input_dev;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_INPUT */

/*
 */

अटल पूर्णांक snd_m3_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_m3 *chip = device->device_data;
	वापस snd_m3_मुक्त(chip);
पूर्ण

अटल पूर्णांक
snd_m3_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci,
	      पूर्णांक enable_amp,
	      पूर्णांक amp_gpio,
	      काष्ठा snd_m3 **chip_ret)
अणु
	काष्ठा snd_m3 *chip;
	पूर्णांक i, err;
	स्थिर काष्ठा snd_pci_quirk *quirk;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_m3_dev_मुक्त,
	पूर्ण;

	*chip_ret = शून्य;

	अगर (pci_enable_device(pci))
		वापस -EIO;

	/* check, अगर we can restrict PCI DMA transfers to 28 bits */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(28))) अणु
		dev_err(card->dev,
			"architecture does not support 28bit PCI busmaster DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&chip->reg_lock);

	चयन (pci->device) अणु
	हाल PCI_DEVICE_ID_ESS_ALLEGRO:
	हाल PCI_DEVICE_ID_ESS_ALLEGRO_1:
	हाल PCI_DEVICE_ID_ESS_CANYON3D_2LE:
	हाल PCI_DEVICE_ID_ESS_CANYON3D_2:
		chip->allegro_flag = 1;
		अवरोध;
	पूर्ण

	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	INIT_WORK(&chip->hwvol_work, snd_m3_update_hw_volume);

	chip->बाह्यal_amp = enable_amp;
	अगर (amp_gpio >= 0 && amp_gpio <= 0x0f)
		chip->amp_gpio = amp_gpio;
	अन्यथा अणु
		quirk = snd_pci_quirk_lookup(pci, m3_amp_quirk_list);
		अगर (quirk) अणु
			dev_info(card->dev, "set amp-gpio for '%s'\n",
				 snd_pci_quirk_name(quirk));
			chip->amp_gpio = quirk->value;
		पूर्ण अन्यथा अगर (chip->allegro_flag)
			chip->amp_gpio = GPO_EXT_AMP_ALLEGRO;
		अन्यथा /* presumably this is क्रम all 'maestro3's.. */
			chip->amp_gpio = GPO_EXT_AMP_M3;
	पूर्ण

	quirk = snd_pci_quirk_lookup(pci, m3_irda_quirk_list);
	अगर (quirk) अणु
		dev_info(card->dev, "enabled irda workaround for '%s'\n",
			 snd_pci_quirk_name(quirk));
		chip->irda_workaround = 1;
	पूर्ण
	quirk = snd_pci_quirk_lookup(pci, m3_hv_quirk_list);
	अगर (quirk)
		chip->hv_config = quirk->value;
	अगर (snd_pci_quirk_lookup(pci, m3_omnibook_quirk_list))
		chip->is_omnibook = 1;

	chip->num_substreams = NR_DSPS;
	chip->substreams = kसुस्मृति(chip->num_substreams, माप(काष्ठा m3_dma),
				   GFP_KERNEL);
	अगर (chip->substreams == शून्य) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	err = request_firmware(&chip->assp_kernel_image,
			       "ess/maestro3_assp_kernel.fw", &pci->dev);
	अगर (err < 0)
		जाओ मुक्त_chip;

	err = request_firmware(&chip->assp_minisrc_image,
			       "ess/maestro3_assp_minisrc.fw", &pci->dev);
	अगर (err < 0)
		जाओ मुक्त_chip;

	err = pci_request_regions(pci, card->driver);
	अगर (err < 0)
		जाओ मुक्त_chip;

	chip->iobase = pci_resource_start(pci, 0);
	
	/* just to be sure */
	pci_set_master(pci);

	snd_m3_chip_init(chip);
	snd_m3_assp_halt(chip);

	snd_m3_ac97_reset(chip);

	snd_m3_amp_enable(chip, 1);

	snd_m3_hv_init(chip);

	अगर (request_irq(pci->irq, snd_m3_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		err = -ENOMEM;
		जाओ मुक्त_chip;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

#अगर_घोषित CONFIG_PM_SLEEP
	chip->suspend_mem =
		vदो_स्मृति(array_size(माप(u16),
				   REV_B_CODE_MEMORY_LENGTH +
					REV_B_DATA_MEMORY_LENGTH));
	अगर (chip->suspend_mem == शून्य)
		dev_warn(card->dev, "can't allocate apm buffer\n");
#पूर्ण_अगर

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0)
		जाओ मुक्त_chip;

	अगर ((err = snd_m3_mixer(chip)) < 0)
		वापस err;

	क्रम (i = 0; i < chip->num_substreams; i++) अणु
		काष्ठा m3_dma *s = &chip->substreams[i];
		अगर ((err = snd_m3_assp_client_init(chip, s, i)) < 0)
			वापस err;
	पूर्ण

	अगर ((err = snd_m3_pcm(chip, 0)) < 0)
		वापस err;

#अगर_घोषित CONFIG_SND_MAESTRO3_INPUT
	अगर (chip->hv_config & HV_CTRL_ENABLE) अणु
		err = snd_m3_input_रेजिस्टर(chip);
		अगर (err)
			dev_warn(card->dev,
				 "Input device registration failed with error %i",
				 err);
	पूर्ण
#पूर्ण_अगर

	snd_m3_enable_पूर्णांकs(chip);
	snd_m3_assp_जारी(chip);

	*chip_ret = chip;

	वापस 0; 

मुक्त_chip:
	snd_m3_मुक्त(chip);
	वापस err;
पूर्ण

/*
 */
अटल पूर्णांक
snd_m3_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_m3 *chip;
	पूर्णांक err;

	/* करोn't pick up modems */
	अगर (((pci->class >> 8) & 0xffff) != PCI_CLASS_MULTIMEDIA_AUDIO)
		वापस -ENODEV;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	चयन (pci->device) अणु
	हाल PCI_DEVICE_ID_ESS_ALLEGRO:
	हाल PCI_DEVICE_ID_ESS_ALLEGRO_1:
		म_नकल(card->driver, "Allegro");
		अवरोध;
	हाल PCI_DEVICE_ID_ESS_CANYON3D_2LE:
	हाल PCI_DEVICE_ID_ESS_CANYON3D_2:
		म_नकल(card->driver, "Canyon3D-2");
		अवरोध;
	शेष:
		म_नकल(card->driver, "Maestro3");
		अवरोध;
	पूर्ण

	err = snd_m3_create(card, pci, बाह्यal_amp[dev], amp_gpio[dev], &chip);
	अगर (err < 0)
		जाओ मुक्त_card;

	card->निजी_data = chip;

	प्र_लिखो(card->लघुname, "ESS %s PCI", card->driver);
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d",
		card->लघुname, chip->iobase, chip->irq);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ मुक्त_card;

#अगर 0 /* TODO: not supported yet */
	/* TODO enable MIDI IRQ and I/O */
	err = snd_mpu401_uart_new(chip->card, 0, MPU401_HW_MPU401,
				  chip->iobase + MPU401_DATA_PORT,
				  MPU401_INFO_INTEGRATED | MPU401_INFO_IRQ_HOOK,
				  -1, &chip->rmidi);
	अगर (err < 0)
		dev_warn(card->dev, "no MIDI support.\n");
#पूर्ण_अगर

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;

मुक्त_card:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_m3_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver m3_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_m3_ids,
	.probe = snd_m3_probe,
	.हटाओ = snd_m3_हटाओ,
	.driver = अणु
		.pm = M3_PM_OPS,
	पूर्ण,
पूर्ण;
	
module_pci_driver(m3_driver);
