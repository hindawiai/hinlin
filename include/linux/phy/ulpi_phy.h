<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/phy/phy.h>

/**
 * Helper that रेजिस्टरs PHY क्रम a ULPI device and adds a lookup क्रम binding it
 * and it's controller, which is always the parent.
 */
अटल अंतरभूत काष्ठा phy
*ulpi_phy_create(काष्ठा ulpi *ulpi, स्थिर काष्ठा phy_ops *ops)
अणु
	काष्ठा phy *phy;
	पूर्णांक ret;

	phy = phy_create(&ulpi->dev, शून्य, ops);
	अगर (IS_ERR(phy))
		वापस phy;

	ret = phy_create_lookup(phy, "usb2-phy", dev_name(ulpi->dev.parent));
	अगर (ret) अणु
		phy_destroy(phy);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस phy;
पूर्ण

/* Remove a PHY that was created with ulpi_phy_create() and it's lookup. */
अटल अंतरभूत व्योम ulpi_phy_destroy(काष्ठा ulpi *ulpi, काष्ठा phy *phy)
अणु
	phy_हटाओ_lookup(phy, "usb2-phy", dev_name(ulpi->dev.parent));
	phy_destroy(phy);
पूर्ण
