<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+
 * Microchip Sparx5 SerDes driver
 *
 * Copyright (c) 2020 Microchip Technology Inc.
 */

#अगर_अघोषित _SPARX5_SERDES_H_
#घोषणा _SPARX5_SERDES_H_

#समावेश "sparx5_serdes_regs.h"

#घोषणा SPX5_SERDES_MAX       33

क्रमागत sparx5_serdes_type अणु
	SPX5_SDT_6G  = 6,
	SPX5_SDT_10G = 10,
	SPX5_SDT_25G = 25,
पूर्ण;

क्रमागत sparx5_serdes_mode अणु
	SPX5_SD_MODE_NONE,
	SPX5_SD_MODE_2G5,
	SPX5_SD_MODE_QSGMII,
	SPX5_SD_MODE_100FX,
	SPX5_SD_MODE_1000BASEX,
	SPX5_SD_MODE_SFI,
पूर्ण;

काष्ठा sparx5_serdes_निजी अणु
	काष्ठा device *dev;
	व्योम __iomem *regs[NUM_TARGETS];
	काष्ठा phy *phys[SPX5_SERDES_MAX];
	bool cmu_enabled;
	अचिन्हित दीर्घ coreघड़ी;
पूर्ण;

काष्ठा sparx5_serdes_macro अणु
	काष्ठा sparx5_serdes_निजी *priv;
	u32 sidx;
	u32 stpidx;
	क्रमागत sparx5_serdes_type serdestype;
	क्रमागत sparx5_serdes_mode serdesmode;
	phy_पूर्णांकerface_t porपंचांगode;
	पूर्णांक speed;
	क्रमागत phy_media media;
पूर्ण;

/* Read, Write and modअगरy रेजिस्टरs content.
 * The रेजिस्टर definition macros start at the id
 */
अटल अंतरभूत व्योम __iomem *sdx5_addr(व्योम __iomem *base[],
				      पूर्णांक id, पूर्णांक tinst, पूर्णांक tcnt,
				      पूर्णांक gbase, पूर्णांक ginst,
				      पूर्णांक gcnt, पूर्णांक gwidth,
				      पूर्णांक raddr, पूर्णांक rinst,
				      पूर्णांक rcnt, पूर्णांक rwidth)
अणु
	WARN_ON((tinst) >= tcnt);
	WARN_ON((ginst) >= gcnt);
	WARN_ON((rinst) >= rcnt);
	वापस base[id + (tinst)] +
		gbase + ((ginst) * gwidth) +
		raddr + ((rinst) * rwidth);
पूर्ण

अटल अंतरभूत व्योम __iomem *sdx5_inst_baseaddr(व्योम __iomem *base,
					       पूर्णांक gbase, पूर्णांक ginst,
					       पूर्णांक gcnt, पूर्णांक gwidth,
					       पूर्णांक raddr, पूर्णांक rinst,
					       पूर्णांक rcnt, पूर्णांक rwidth)
अणु
	WARN_ON((ginst) >= gcnt);
	WARN_ON((rinst) >= rcnt);
	वापस base +
		gbase + ((ginst) * gwidth) +
		raddr + ((rinst) * rwidth);
पूर्ण

अटल अंतरभूत व्योम sdx5_rmw(u32 val, u32 mask, काष्ठा sparx5_serdes_निजी *priv,
			    पूर्णांक id, पूर्णांक tinst, पूर्णांक tcnt,
			    पूर्णांक gbase, पूर्णांक ginst, पूर्णांक gcnt, पूर्णांक gwidth,
			    पूर्णांक raddr, पूर्णांक rinst, पूर्णांक rcnt, पूर्णांक rwidth)
अणु
	u32 nval;
	व्योम __iomem *addr =
		sdx5_addr(priv->regs, id, tinst, tcnt,
			  gbase, ginst, gcnt, gwidth,
			  raddr, rinst, rcnt, rwidth);
	nval = पढ़ोl(addr);
	nval = (nval & ~mask) | (val & mask);
	ग_लिखोl(nval, addr);
पूर्ण

अटल अंतरभूत व्योम sdx5_inst_rmw(u32 val, u32 mask, व्योम __iomem *iomem,
				 पूर्णांक id, पूर्णांक tinst, पूर्णांक tcnt,
				 पूर्णांक gbase, पूर्णांक ginst, पूर्णांक gcnt, पूर्णांक gwidth,
				 पूर्णांक raddr, पूर्णांक rinst, पूर्णांक rcnt, पूर्णांक rwidth)
अणु
	u32 nval;
	व्योम __iomem *addr =
		sdx5_inst_baseaddr(iomem,
				   gbase, ginst, gcnt, gwidth,
				   raddr, rinst, rcnt, rwidth);
	nval = पढ़ोl(addr);
	nval = (nval & ~mask) | (val & mask);
	ग_लिखोl(nval, addr);
पूर्ण

अटल अंतरभूत व्योम sdx5_rmw_addr(u32 val, u32 mask, व्योम __iomem *addr)
अणु
	u32 nval;

	nval = पढ़ोl(addr);
	nval = (nval & ~mask) | (val & mask);
	ग_लिखोl(nval, addr);
पूर्ण

अटल अंतरभूत व्योम __iomem *sdx5_inst_get(काष्ठा sparx5_serdes_निजी *priv,
					  पूर्णांक id, पूर्णांक tinst)
अणु
	वापस priv->regs[id + tinst];
पूर्ण

अटल अंतरभूत व्योम __iomem *sdx5_inst_addr(व्योम __iomem *iomem,
					   पूर्णांक id, पूर्णांक tinst, पूर्णांक tcnt,
					   पूर्णांक gbase,
					   पूर्णांक ginst, पूर्णांक gcnt, पूर्णांक gwidth,
					   पूर्णांक raddr,
					   पूर्णांक rinst, पूर्णांक rcnt, पूर्णांक rwidth)
अणु
	वापस sdx5_inst_baseaddr(iomem, gbase, ginst, gcnt, gwidth,
				  raddr, rinst, rcnt, rwidth);
पूर्ण


#पूर्ण_अगर /* _SPARX5_SERDES_REGS_H_ */
