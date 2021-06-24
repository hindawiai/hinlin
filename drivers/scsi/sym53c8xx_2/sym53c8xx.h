<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Device driver क्रम the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family 
 * of PCI-SCSI IO processors.
 *
 * Copyright (C) 1999-2001  Gerard Roudier <groudier@मुक्त.fr>
 *
 * This driver is derived from the Linux sym53c8xx driver.
 * Copyright (C) 1998-2000  Gerard Roudier
 *
 * The sym53c8xx driver is derived from the ncr53c8xx driver that had been 
 * a port of the FreeBSD ncr driver to Linux-1.2.13.
 *
 * The original ncr driver has been written क्रम 386bsd and FreeBSD by
 *         Wolfgang Stanglmeier        <wolf@cologne.de>
 *         Stefan Esser                <se@mi.Uni-Koeln.de>
 * Copyright (C) 1994  Wolfgang Stanglmeier
 *
 * Other major contributions:
 *
 * NVRAM detection and पढ़ोing.
 * Copyright (C) 1997 Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#अगर_अघोषित SYM53C8XX_H
#घोषणा SYM53C8XX_H


/*
 *  DMA addressing mode.
 *
 *  0 : 32 bit addressing क्रम all chips.
 *  1 : 40 bit addressing when supported by chip.
 *  2 : 64 bit addressing when supported by chip,
 *      limited to 16 segments of 4 GB -> 64 GB max.
 */
#घोषणा	SYM_CONF_DMA_ADDRESSING_MODE CONFIG_SCSI_SYM53C8XX_DMA_ADDRESSING_MODE

/*
 *  NVRAM support.
 */
#अगर 1
#घोषणा SYM_CONF_NVRAM_SUPPORT		(1)
#पूर्ण_अगर

/*
 *  These options are not tunable from 'make config'
 */
#अगर 1
#घोषणा	SYM_LINUX_PROC_INFO_SUPPORT
#घोषणा SYM_LINUX_USER_COMMAND_SUPPORT
#घोषणा SYM_LINUX_USER_INFO_SUPPORT
#घोषणा SYM_LINUX_DEBUG_CONTROL_SUPPORT
#पूर्ण_अगर

/*
 *  Also handle old NCR chips अगर not (0).
 */
#घोषणा SYM_CONF_GENERIC_SUPPORT	(1)

/*
 *  Allow tags from 2 to 256, शेष 8
 */
#अगर_अघोषित CONFIG_SCSI_SYM53C8XX_MAX_TAGS
#घोषणा CONFIG_SCSI_SYM53C8XX_MAX_TAGS	(8)
#पूर्ण_अगर

#अगर	CONFIG_SCSI_SYM53C8XX_MAX_TAGS < 2
#घोषणा SYM_CONF_MAX_TAG	(2)
#या_अगर	CONFIG_SCSI_SYM53C8XX_MAX_TAGS > 256
#घोषणा SYM_CONF_MAX_TAG	(256)
#अन्यथा
#घोषणा	SYM_CONF_MAX_TAG	CONFIG_SCSI_SYM53C8XX_MAX_TAGS
#पूर्ण_अगर

#अगर_अघोषित	CONFIG_SCSI_SYM53C8XX_DEFAULT_TAGS
#घोषणा	CONFIG_SCSI_SYM53C8XX_DEFAULT_TAGS	SYM_CONF_MAX_TAG
#पूर्ण_अगर

/*
 *  Anyway, we configure the driver क्रम at least 64 tags per LUN. :)
 */
#अगर	SYM_CONF_MAX_TAG <= 64
#घोषणा SYM_CONF_MAX_TAG_ORDER	(6)
#या_अगर	SYM_CONF_MAX_TAG <= 128
#घोषणा SYM_CONF_MAX_TAG_ORDER	(7)
#अन्यथा
#घोषणा SYM_CONF_MAX_TAG_ORDER	(8)
#पूर्ण_अगर

/*
 *  Max number of SG entries.
 */
#घोषणा SYM_CONF_MAX_SG		(96)

/*
 *  Driver setup काष्ठाure.
 *
 *  This काष्ठाure is initialized from linux config options.
 *  It can be overridden at boot-up by the boot command line.
 */
काष्ठा sym_driver_setup अणु
	u_लघु	max_tag;
	u_अक्षर	burst_order;
	u_अक्षर	scsi_led;
	u_अक्षर	scsi_dअगरf;
	u_अक्षर	irq_mode;
	u_अक्षर	scsi_bus_check;
	u_अक्षर	host_id;

	u_अक्षर	verbose;
	u_अक्षर	settle_delay;
	u_अक्षर	use_nvram;
	u_दीर्घ	excludes[8];
पूर्ण;

#घोषणा SYM_SETUP_MAX_TAG		sym_driver_setup.max_tag
#घोषणा SYM_SETUP_BURST_ORDER		sym_driver_setup.burst_order
#घोषणा SYM_SETUP_SCSI_LED		sym_driver_setup.scsi_led
#घोषणा SYM_SETUP_SCSI_DIFF		sym_driver_setup.scsi_dअगरf
#घोषणा SYM_SETUP_IRQ_MODE		sym_driver_setup.irq_mode
#घोषणा SYM_SETUP_SCSI_BUS_CHECK	sym_driver_setup.scsi_bus_check
#घोषणा SYM_SETUP_HOST_ID		sym_driver_setup.host_id
#घोषणा boot_verbose			sym_driver_setup.verbose

/*
 *  Initial setup.
 *
 *  Can be overriden at startup by a command line.
 */
#घोषणा SYM_LINUX_DRIVER_SETUP	अणु				\
	.max_tag	= CONFIG_SCSI_SYM53C8XX_DEFAULT_TAGS,	\
	.burst_order	= 7,					\
	.scsi_led	= 1,					\
	.scsi_dअगरf	= 1,					\
	.irq_mode	= 0,					\
	.scsi_bus_check	= 1,					\
	.host_id	= 7,					\
	.verbose	= 0,					\
	.settle_delay	= 3,					\
	.use_nvram	= 1,					\
पूर्ण

बाह्य काष्ठा sym_driver_setup sym_driver_setup;
बाह्य अचिन्हित पूर्णांक sym_debug_flags;
#घोषणा DEBUG_FLAGS	sym_debug_flags

/*
 *  Max number of tarमाला_लो.
 *  Maximum is 16 and you are advised not to change this value.
 */
#अगर_अघोषित SYM_CONF_MAX_TARGET
#घोषणा SYM_CONF_MAX_TARGET	(16)
#पूर्ण_अगर

/*
 *  Max number of logical units.
 *  SPI-2 allows up to 64 logical units, but in real lअगरe, target
 *  that implements more that 7 logical units are pretty rare.
 *  Anyway, the cost of accepting up to 64 logical unit is low in 
 *  this driver, thus going with the maximum is acceptable.
 */
#अगर_अघोषित SYM_CONF_MAX_LUN
#घोषणा SYM_CONF_MAX_LUN	(64)
#पूर्ण_अगर

/*
 *  Max number of IO control blocks queued to the controller.
 *  Each entry needs 8 bytes and the queues are allocated contiguously.
 *  Since we करोnnot want to allocate more than a page, the theorical 
 *  maximum is PAGE_SIZE/8. For safety, we announce a bit less to the 
 *  access method. :)
 *  When not supplied, as it is suggested, the driver compute some 
 *  good value क्रम this parameter.
 */
/* #घोषणा SYM_CONF_MAX_START	(PAGE_SIZE/8 - 16) */

/*
 *  Support क्रम Immediate Arbitration.
 *  Not advised.
 */
/* #घोषणा SYM_CONF_IARB_SUPPORT */

/*
 *  Only relevant अगर IARB support configured.
 *  - Max number of successive settings of IARB hपूर्णांकs.
 *  - Set IARB on arbitration lost.
 */
#घोषणा SYM_CONF_IARB_MAX 3
#घोषणा SYM_CONF_SET_IARB_ON_ARB_LOST 1

/*
 *  Returning wrong residuals may make problems.
 *  When zero, this define tells the driver to 
 *  always वापस 0 as transfer residual.
 *  Btw, all my testings of residuals have succeeded.
 */
#घोषणा SYM_SETUP_RESIDUAL_SUPPORT 1

#पूर्ण_अगर /* SYM53C8XX_H */
