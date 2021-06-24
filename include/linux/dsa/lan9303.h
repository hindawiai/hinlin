<शैली गुरु>
/* Included by drivers/net/dsa/lan9303.h and net/dsa/tag_lan9303.c */
#समावेश <linux/अगर_ether.h>

काष्ठा lan9303;

काष्ठा lan9303_phy_ops अणु
	/* PHY 1 and 2 access*/
	पूर्णांक	(*phy_पढ़ो)(काष्ठा lan9303 *chip, पूर्णांक port, पूर्णांक regnum);
	पूर्णांक	(*phy_ग_लिखो)(काष्ठा lan9303 *chip, पूर्णांक port,
			     पूर्णांक regnum, u16 val);
पूर्ण;

#घोषणा LAN9303_NUM_ALR_RECORDS 512
काष्ठा lan9303_alr_cache_entry अणु
	u8  mac_addr[ETH_ALEN];
	u8  port_map;         /* Biपंचांगap of ports. Zero अगर unused entry */
	u8  stp_override;     /* non zero अगर set LAN9303_ALR_DAT1_AGE_OVERRID */
पूर्ण;

काष्ठा lan9303 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *irq_data;
	काष्ठा gpio_desc *reset_gpio;
	u32 reset_duration; /* in [ms] */
	पूर्णांक phy_addr_base;
	काष्ठा dsa_चयन *ds;
	काष्ठा mutex indirect_mutex; /* protect indexed रेजिस्टर access */
	काष्ठा mutex alr_mutex; /* protect ALR access */
	स्थिर काष्ठा lan9303_phy_ops *ops;
	bool is_bridged; /* true अगर port 1 and 2 are bridged */

	/* remember LAN9303_SWE_PORT_STATE जबतक not bridged */
	u32 swe_port_state;
	/* LAN9303 करो not offer पढ़ोing specअगरic ALR entry. Cache all
	 * अटल entries in a flat table
	 **/
	काष्ठा lan9303_alr_cache_entry alr_cache[LAN9303_NUM_ALR_RECORDS];
पूर्ण;
