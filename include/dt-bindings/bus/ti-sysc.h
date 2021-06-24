<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* TI sysc पूर्णांकerconnect target module defines */

/* Generic sysc found on omap2 and later, also known as type1 */
#घोषणा SYSC_OMAP2_CLOCKACTIVITY	(3 << 8)
#घोषणा SYSC_OMAP2_EMUFREE		(1 << 5)
#घोषणा SYSC_OMAP2_ENAWAKEUP		(1 << 2)
#घोषणा SYSC_OMAP2_SOFTRESET		(1 << 1)
#घोषणा SYSC_OMAP2_AUTOIDLE		(1 << 0)

/* Generic sysc found on omap4 and later, also known as type2 */
#घोषणा SYSC_OMAP4_DMADISABLE		(1 << 16)
#घोषणा SYSC_OMAP4_FREEEMU		(1 << 1)	/* Also known as EMUFREE */
#घोषणा SYSC_OMAP4_SOFTRESET		(1 << 0)

/* SmartReflex sysc found on 36xx and later */
#घोषणा SYSC_OMAP3_SR_ENAWAKEUP		(1 << 26)

#घोषणा SYSC_DRA7_MCAN_ENAWAKEUP	(1 << 4)

/* PRUSS sysc found on AM33xx/AM43xx/AM57xx */
#घोषणा SYSC_PRUSS_SUB_MWAIT		(1 << 5)
#घोषणा SYSC_PRUSS_STANDBY_INIT		(1 << 4)

/* SYSCONFIG STANDBYMODE/MIDLEMODE/SIDLEMODE supported by hardware */
#घोषणा SYSC_IDLE_FORCE			0
#घोषणा SYSC_IDLE_NO			1
#घोषणा SYSC_IDLE_SMART			2
#घोषणा SYSC_IDLE_SMART_WKUP		3
