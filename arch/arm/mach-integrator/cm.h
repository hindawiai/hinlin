<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * access the core module control रेजिस्टर.
 */
u32 cm_get(व्योम);
व्योम cm_control(u32, u32);

काष्ठा device_node;
व्योम cm_init(व्योम);
व्योम cm_clear_irqs(व्योम);

#घोषणा CM_CTRL_LED			(1 << 0)
#घोषणा CM_CTRL_nMBDET			(1 << 1)
#घोषणा CM_CTRL_REMAP			(1 << 2)

/*
 * Integrator/AP,PP2 specअगरic
 */
#घोषणा CM_CTRL_HIGHVECTORS		(1 << 4)
#घोषणा CM_CTRL_BIGENDIAN		(1 << 5)
#घोषणा CM_CTRL_FASTBUS			(1 << 6)
#घोषणा CM_CTRL_SYNC			(1 << 7)

/*
 * ARM926/946/966 Integrator/CP specअगरic
 */
#घोषणा CM_CTRL_LCDBIASEN		(1 << 8)
#घोषणा CM_CTRL_LCDBIASUP		(1 << 9)
#घोषणा CM_CTRL_LCDBIASDN		(1 << 10)
#घोषणा CM_CTRL_LCDMUXSEL_MASK		(7 << 11)
#घोषणा CM_CTRL_LCDMUXSEL_GENLCD	(1 << 11)
#घोषणा CM_CTRL_LCDMUXSEL_VGA565_TFT555	(2 << 11)
#घोषणा CM_CTRL_LCDMUXSEL_SHARPLCD	(3 << 11)
#घोषणा CM_CTRL_LCDMUXSEL_VGA555_TFT555	(4 << 11)
#घोषणा CM_CTRL_LCDEN0			(1 << 14)
#घोषणा CM_CTRL_LCDEN1			(1 << 15)
#घोषणा CM_CTRL_STATIC1			(1 << 16)
#घोषणा CM_CTRL_STATIC2			(1 << 17)
#घोषणा CM_CTRL_STATIC			(1 << 18)
#घोषणा CM_CTRL_n24BITEN		(1 << 19)
#घोषणा CM_CTRL_EBIWP			(1 << 20)
