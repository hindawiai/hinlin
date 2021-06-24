<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/fsl_devices.h
 *
 * Definitions क्रम any platक्रमm device related flags or काष्ठाures क्रम
 * Freescale processor devices
 *
 * Maपूर्णांकainer: Kumar Gala <galak@kernel.crashing.org>
 *
 * Copyright 2004,2012 Freescale Semiconductor, Inc
 */

#अगर_अघोषित _FSL_DEVICE_H_
#घोषणा _FSL_DEVICE_H_

#घोषणा FSL_UTMI_PHY_DLY	10	/*As per P1010RM, delay क्रम UTMI
				PHY CLK to become stable - 10ms*/
#घोषणा FSL_USB_PHY_CLK_TIMEOUT	10000	/* uSec */

#समावेश <linux/types.h>

/*
 * Some conventions on how we handle peripherals on Freescale chips
 *
 * unique device: a platक्रमm_device entry in fsl_plat_devs[] plus
 * associated device inक्रमmation in its platक्रमm_data काष्ठाure.
 *
 * A chip is described by a set of unique devices.
 *
 * Each sub-arch has its own master list of unique devices and
 * क्रमागतerates them by क्रमागत fsl_devices in a sub-arch specअगरic header
 *
 * The platक्रमm data काष्ठाure is broken पूर्णांकo two parts.  The
 * first is device specअगरic inक्रमmation that help identअगरy any
 * unique features of a peripheral.  The second is any
 * inक्रमmation that may be defined by the board or how the device
 * is connected बाह्यally of the chip.
 *
 * naming conventions:
 * - platक्रमm data काष्ठाures: <driver>_platक्रमm_data
 * - platक्रमm data device flags: FSL_<driver>_DEV_<FLAG>
 * - platक्रमm data board flags: FSL_<driver>_BRD_<FLAG>
 *
 */

क्रमागत fsl_usb2_controller_ver अणु
	FSL_USB_VER_NONE = -1,
	FSL_USB_VER_OLD = 0,
	FSL_USB_VER_1_6 = 1,
	FSL_USB_VER_2_2 = 2,
	FSL_USB_VER_2_4 = 3,
	FSL_USB_VER_2_5 = 4,
पूर्ण;

क्रमागत fsl_usb2_operating_modes अणु
	FSL_USB2_MPH_HOST,
	FSL_USB2_DR_HOST,
	FSL_USB2_DR_DEVICE,
	FSL_USB2_DR_OTG,
पूर्ण;

क्रमागत fsl_usb2_phy_modes अणु
	FSL_USB2_PHY_NONE,
	FSL_USB2_PHY_ULPI,
	FSL_USB2_PHY_UTMI,
	FSL_USB2_PHY_UTMI_WIDE,
	FSL_USB2_PHY_SERIAL,
	FSL_USB2_PHY_UTMI_DUAL,
पूर्ण;

काष्ठा clk;
काष्ठा platक्रमm_device;

काष्ठा fsl_usb2_platक्रमm_data अणु
	/* board specअगरic inक्रमmation */
	क्रमागत fsl_usb2_controller_ver	controller_ver;
	क्रमागत fsl_usb2_operating_modes	operating_mode;
	क्रमागत fsl_usb2_phy_modes		phy_mode;
	अचिन्हित पूर्णांक			port_enables;
	अचिन्हित पूर्णांक			workaround;

	पूर्णांक		(*init)(काष्ठा platक्रमm_device *);
	व्योम		(*निकास)(काष्ठा platक्रमm_device *);
	व्योम __iomem	*regs;		/* ioremap'd रेजिस्टर base */
	काष्ठा clk	*clk;
	अचिन्हित	घातer_budget;	/* hcd->घातer_budget */
	अचिन्हित	big_endian_mmio:1;
	अचिन्हित	big_endian_desc:1;
	अचिन्हित	es:1;		/* need USBMODE:ES */
	अचिन्हित	le_setup_buf:1;
	अचिन्हित	have_sysअगर_regs:1;
	अचिन्हित	invert_drvvbus:1;
	अचिन्हित	invert_pwr_fault:1;

	अचिन्हित	suspended:1;
	अचिन्हित	alपढ़ोy_suspended:1;
	अचिन्हित	has_fsl_erratum_a007792:1;
	अचिन्हित	has_fsl_erratum_14:1;
	अचिन्हित	has_fsl_erratum_a005275:1;
	अचिन्हित	has_fsl_erratum_a005697:1;
	अचिन्हित        has_fsl_erratum_a006918:1;
	अचिन्हित	check_phy_clk_valid:1;

	/* रेजिस्टर save area क्रम suspend/resume */
	u32		pm_command;
	u32		pm_status;
	u32		pm_पूर्णांकr_enable;
	u32		pm_frame_index;
	u32		pm_segment;
	u32		pm_frame_list;
	u32		pm_async_next;
	u32		pm_configured_flag;
	u32		pm_portsc;
	u32		pm_usbgenctrl;
पूर्ण;

/* Flags in fsl_usb2_mph_platक्रमm_data */
#घोषणा FSL_USB2_PORT0_ENABLED	0x00000001
#घोषणा FSL_USB2_PORT1_ENABLED	0x00000002

#घोषणा FLS_USB2_WORKAROUND_ENGCM09152	(1 << 0)

काष्ठा spi_device;

काष्ठा fsl_spi_platक्रमm_data अणु
	u32 	initial_spmode;	/* initial SPMODE value */
	s16	bus_num;
	अचिन्हित पूर्णांक flags;
#घोषणा SPI_QE_CPU_MODE		(1 << 0) /* QE CPU ("PIO") mode */
#घोषणा SPI_CPM_MODE		(1 << 1) /* CPM/QE ("DMA") mode */
#घोषणा SPI_CPM1		(1 << 2) /* SPI unit is in CPM1 block */
#घोषणा SPI_CPM2		(1 << 3) /* SPI unit is in CPM2 block */
#घोषणा SPI_QE			(1 << 4) /* SPI unit is in QE block */
	/* board specअगरic inक्रमmation */
	u16	max_chipselect;
	व्योम	(*cs_control)(काष्ठा spi_device *spi, bool on);
	u32	sysclk;
पूर्ण;

काष्ठा mpc8xx_pcmcia_ops अणु
	व्योम(*hw_ctrl)(पूर्णांक slot, पूर्णांक enable);
	पूर्णांक(*voltage_set)(पूर्णांक slot, पूर्णांक vcc, पूर्णांक vpp);
पूर्ण;

/* Returns non-zero अगर the current suspend operation would
 * lead to a deep sleep (i.e. घातer हटाओd from the core,
 * instead of just the घड़ी).
 */
#अगर defined(CONFIG_PPC_83xx) && defined(CONFIG_SUSPEND)
पूर्णांक fsl_deep_sleep(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक fsl_deep_sleep(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _FSL_DEVICE_H_ */
