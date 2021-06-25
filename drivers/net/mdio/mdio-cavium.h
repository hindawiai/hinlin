<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2009-2016 Cavium, Inc.
 */

क्रमागत cavium_mdiobus_mode अणु
	UNINIT = 0,
	C22,
	C45
पूर्ण;

#घोषणा SMI_CMD		0x0
#घोषणा SMI_WR_DAT	0x8
#घोषणा SMI_RD_DAT	0x10
#घोषणा SMI_CLK		0x18
#घोषणा SMI_EN		0x20

#अगर_घोषित __BIG_ENDIAN_BITFIELD
#घोषणा OCT_MDIO_BITFIELD_FIELD(field, more)	\
	field;					\
	more

#अन्यथा
#घोषणा OCT_MDIO_BITFIELD_FIELD(field, more)	\
	more					\
	field;

#पूर्ण_अगर

जोड़ cvmx_smix_clk अणु
	u64 u64;
	काष्ठा cvmx_smix_clk_s अणु
	  OCT_MDIO_BITFIELD_FIELD(u64 reserved_25_63:39,
	  OCT_MDIO_BITFIELD_FIELD(u64 mode:1,
	  OCT_MDIO_BITFIELD_FIELD(u64 reserved_21_23:3,
	  OCT_MDIO_BITFIELD_FIELD(u64 sample_hi:5,
	  OCT_MDIO_BITFIELD_FIELD(u64 sample_mode:1,
	  OCT_MDIO_BITFIELD_FIELD(u64 reserved_14_14:1,
	  OCT_MDIO_BITFIELD_FIELD(u64 clk_idle:1,
	  OCT_MDIO_BITFIELD_FIELD(u64 preamble:1,
	  OCT_MDIO_BITFIELD_FIELD(u64 sample:4,
	  OCT_MDIO_BITFIELD_FIELD(u64 phase:8,
	  ;))))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_smix_cmd अणु
	u64 u64;
	काष्ठा cvmx_smix_cmd_s अणु
	  OCT_MDIO_BITFIELD_FIELD(u64 reserved_18_63:46,
	  OCT_MDIO_BITFIELD_FIELD(u64 phy_op:2,
	  OCT_MDIO_BITFIELD_FIELD(u64 reserved_13_15:3,
	  OCT_MDIO_BITFIELD_FIELD(u64 phy_adr:5,
	  OCT_MDIO_BITFIELD_FIELD(u64 reserved_5_7:3,
	  OCT_MDIO_BITFIELD_FIELD(u64 reg_adr:5,
	  ;))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_smix_en अणु
	u64 u64;
	काष्ठा cvmx_smix_en_s अणु
	  OCT_MDIO_BITFIELD_FIELD(u64 reserved_1_63:63,
	  OCT_MDIO_BITFIELD_FIELD(u64 en:1,
	  ;))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_smix_rd_dat अणु
	u64 u64;
	काष्ठा cvmx_smix_rd_dat_s अणु
	  OCT_MDIO_BITFIELD_FIELD(u64 reserved_18_63:46,
	  OCT_MDIO_BITFIELD_FIELD(u64 pending:1,
	  OCT_MDIO_BITFIELD_FIELD(u64 val:1,
	  OCT_MDIO_BITFIELD_FIELD(u64 dat:16,
	  ;))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_smix_wr_dat अणु
	u64 u64;
	काष्ठा cvmx_smix_wr_dat_s अणु
	  OCT_MDIO_BITFIELD_FIELD(u64 reserved_18_63:46,
	  OCT_MDIO_BITFIELD_FIELD(u64 pending:1,
	  OCT_MDIO_BITFIELD_FIELD(u64 val:1,
	  OCT_MDIO_BITFIELD_FIELD(u64 dat:16,
	  ;))))
	पूर्ण s;
पूर्ण;

काष्ठा cavium_mdiobus अणु
	काष्ठा mii_bus *mii_bus;
	व्योम __iomem *रेजिस्टर_base;
	क्रमागत cavium_mdiobus_mode mode;
पूर्ण;

#अगर_घोषित CONFIG_CAVIUM_OCTEON_SOC

#समावेश <यंत्र/octeon/octeon.h>

अटल अंतरभूत व्योम oct_mdio_ग_लिखोq(u64 val, व्योम __iomem *addr)
अणु
	cvmx_ग_लिखो_csr((u64 __क्रमce)addr, val);
पूर्ण

अटल अंतरभूत u64 oct_mdio_पढ़ोq(व्योम __iomem *addr)
अणु
	वापस cvmx_पढ़ो_csr((u64 __क्रमce)addr);
पूर्ण
#अन्यथा
#समावेश <linux/io-64-nonatomic-lo-hi.h>

#घोषणा oct_mdio_ग_लिखोq(val, addr)	ग_लिखोq(val, addr)
#घोषणा oct_mdio_पढ़ोq(addr)		पढ़ोq(addr)
#पूर्ण_अगर

पूर्णांक cavium_mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum);
पूर्णांक cavium_mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum, u16 val);
