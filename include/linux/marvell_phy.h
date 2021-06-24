<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MARVELL_PHY_H
#घोषणा _MARVELL_PHY_H

/* Mask used क्रम ID comparisons */
#घोषणा MARVELL_PHY_ID_MASK		0xfffffff0

/* Known PHY IDs */
#घोषणा MARVELL_PHY_ID_88E1101		0x01410c60
#घोषणा MARVELL_PHY_ID_88E1112		0x01410c90
#घोषणा MARVELL_PHY_ID_88E1111		0x01410cc0
#घोषणा MARVELL_PHY_ID_88E1118		0x01410e10
#घोषणा MARVELL_PHY_ID_88E1121R		0x01410cb0
#घोषणा MARVELL_PHY_ID_88E1145		0x01410cd0
#घोषणा MARVELL_PHY_ID_88E1149R		0x01410e50
#घोषणा MARVELL_PHY_ID_88E1240		0x01410e30
#घोषणा MARVELL_PHY_ID_88E1318S		0x01410e90
#घोषणा MARVELL_PHY_ID_88E1340S		0x01410dc0
#घोषणा MARVELL_PHY_ID_88E1116R		0x01410e40
#घोषणा MARVELL_PHY_ID_88E1510		0x01410dd0
#घोषणा MARVELL_PHY_ID_88E1540		0x01410eb0
#घोषणा MARVELL_PHY_ID_88E1545		0x01410ea0
#घोषणा MARVELL_PHY_ID_88E1548P		0x01410ec0
#घोषणा MARVELL_PHY_ID_88E3016		0x01410e60
#घोषणा MARVELL_PHY_ID_88E2110		0x002b09b0
#घोषणा MARVELL_PHY_ID_88X2222		0x01410f10

/* PHY IDs and mask क्रम Alaska 10G PHYs */
#घोषणा MARVELL_PHY_ID_88X33X0_MASK	0xfffffff8
#घोषणा MARVELL_PHY_ID_88X3310		0x002b09a0
#घोषणा MARVELL_PHY_ID_88X3340		0x002b09a8

/* Marvel 88E1111 in Finisar SFP module with modअगरied PHY ID */
#घोषणा MARVELL_PHY_ID_88E1111_FINISAR	0x01ff0cc0

/* These Ethernet चयन families contain embedded PHYs, but they करो
 * not have a model ID. So the चयन driver traps पढ़ोs to the ID2
 * रेजिस्टर and वापसs the चयन family ID
 */
#घोषणा MARVELL_PHY_ID_88E6341_FAMILY	0x01410f41
#घोषणा MARVELL_PHY_ID_88E6390_FAMILY	0x01410f90
#घोषणा MARVELL_PHY_ID_88E6393_FAMILY	0x002b0b9b

#घोषणा MARVELL_PHY_FAMILY_ID(id)	((id) >> 4)

/* काष्ठा phy_device dev_flags definitions */
#घोषणा MARVELL_PHY_M1145_FLAGS_RESISTANCE	0x00000001
#घोषणा MARVELL_PHY_M1118_DNS323_LEDS		0x00000002
#घोषणा MARVELL_PHY_LED0_LINK_LED1_ACTIVE	0x00000004

#पूर्ण_अगर /* _MARVELL_PHY_H */
