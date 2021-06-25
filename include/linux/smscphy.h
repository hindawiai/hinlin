<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SMSCPHY_H__
#घोषणा __LINUX_SMSCPHY_H__

#घोषणा MII_LAN83C185_ISF 29 /* Interrupt Source Flags */
#घोषणा MII_LAN83C185_IM  30 /* Interrupt Mask */
#घोषणा MII_LAN83C185_CTRL_STATUS 17 /* Mode/Status Register */
#घोषणा MII_LAN83C185_SPECIAL_MODES 18 /* Special Modes Register */

#घोषणा MII_LAN83C185_ISF_INT1 (1<<1) /* Auto-Negotiation Page Received */
#घोषणा MII_LAN83C185_ISF_INT2 (1<<2) /* Parallel Detection Fault */
#घोषणा MII_LAN83C185_ISF_INT3 (1<<3) /* Auto-Negotiation LP Ack */
#घोषणा MII_LAN83C185_ISF_INT4 (1<<4) /* Link Down */
#घोषणा MII_LAN83C185_ISF_INT5 (1<<5) /* Remote Fault Detected */
#घोषणा MII_LAN83C185_ISF_INT6 (1<<6) /* Auto-Negotiation complete */
#घोषणा MII_LAN83C185_ISF_INT7 (1<<7) /* ENERGYON */

#घोषणा MII_LAN83C185_ISF_INT_ALL (0x0e)

#घोषणा MII_LAN83C185_ISF_INT_PHYLIB_EVENTS \
	(MII_LAN83C185_ISF_INT6 | MII_LAN83C185_ISF_INT4 | \
	 MII_LAN83C185_ISF_INT7)

#घोषणा MII_LAN83C185_EDPWRDOWN (1 << 13) /* EDPWRDOWN */
#घोषणा MII_LAN83C185_ENERGYON  (1 << 1)  /* ENERGYON */

#घोषणा MII_LAN83C185_MODE_MASK      0xE0
#घोषणा MII_LAN83C185_MODE_POWERDOWN 0xC0 /* Power Down mode */
#घोषणा MII_LAN83C185_MODE_ALL       0xE0 /* All capable mode */

#पूर्ण_अगर /* __LINUX_SMSCPHY_H__ */
