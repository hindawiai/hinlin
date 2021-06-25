<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __COM9026_H
#घोषणा __COM9026_H

/* COM 9026 controller chip --> ARCnet रेजिस्टर addresses */

#घोषणा COM9026_REG_W_INTMASK	0	/* writable */
#घोषणा COM9026_REG_R_STATUS	0	/* पढ़ोable */
#घोषणा COM9026_REG_W_COMMAND	1	/* writable, वापसs अक्रमom vals on पढ़ो (?) */
#घोषणा COM9026_REG_RW_CONFIG	2	/* Configuration रेजिस्टर */
#घोषणा COM9026_REG_R_RESET	8	/* software reset (on पढ़ो) */
#घोषणा COM9026_REG_RW_MEMDATA	12	/* Data port क्रम IO-mapped memory */
#घोषणा COM9026_REG_W_ADDR_LO	14	/* Control रेजिस्टरs क्रम said */
#घोषणा COM9026_REG_W_ADDR_HI	15

#घोषणा COM9026_REG_R_STATION	1	/* Station ID */

#पूर्ण_अगर
