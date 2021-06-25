<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 Linaro Ltd
 */

#अगर_अघोषित __DRIVERS_INTERCONNECT_QCOM_ICC_RPM_H
#घोषणा __DRIVERS_INTERCONNECT_QCOM_ICC_RPM_H

#घोषणा RPM_BUS_MASTER_REQ	0x73616d62
#घोषणा RPM_BUS_SLAVE_REQ	0x766c7362

#घोषणा QCOM_MAX_LINKS 12

#घोषणा to_qcom_provider(_provider) \
	container_of(_provider, काष्ठा qcom_icc_provider, provider)

/**
 * काष्ठा qcom_icc_provider - Qualcomm specअगरic पूर्णांकerconnect provider
 * @provider: generic पूर्णांकerconnect provider
 * @bus_clks: the clk_bulk_data table of bus घड़ीs
 * @num_clks: the total number of clk_bulk_data entries
 */
काष्ठा qcom_icc_provider अणु
	काष्ठा icc_provider provider;
	काष्ठा clk_bulk_data *bus_clks;
	पूर्णांक num_clks;
पूर्ण;

/**
 * काष्ठा qcom_icc_node - Qualcomm specअगरic पूर्णांकerconnect nodes
 * @name: the node name used in debugfs
 * @id: a unique node identअगरier
 * @links: an array of nodes where we can go next जबतक traversing
 * @num_links: the total number of @links
 * @buswidth: width of the पूर्णांकerconnect between a node and the bus (bytes)
 * @mas_rpm_id:	RPM id क्रम devices that are bus masters
 * @slv_rpm_id:	RPM id क्रम devices that are bus slaves
 * @rate: current bus घड़ी rate in Hz
 */
काष्ठा qcom_icc_node अणु
	अचिन्हित अक्षर *name;
	u16 id;
	u16 links[QCOM_MAX_LINKS];
	u16 num_links;
	u16 buswidth;
	पूर्णांक mas_rpm_id;
	पूर्णांक slv_rpm_id;
	u64 rate;
पूर्ण;

काष्ठा qcom_icc_desc अणु
	काष्ठा qcom_icc_node **nodes;
	माप_प्रकार num_nodes;
पूर्ण;

#घोषणा DEFINE_QNODE(_name, _id, _buswidth, _mas_rpm_id, _slv_rpm_id,	\
		     ...)						\
		अटल काष्ठा qcom_icc_node _name = अणु			\
		.name = #_name,						\
		.id = _id,						\
		.buswidth = _buswidth,					\
		.mas_rpm_id = _mas_rpm_id,				\
		.slv_rpm_id = _slv_rpm_id,				\
		.num_links = ARRAY_SIZE(((पूर्णांक[])अणु __VA_ARGS__ पूर्ण)),	\
		.links = अणु __VA_ARGS__ पूर्ण,				\
	पूर्ण


पूर्णांक qnoc_probe(काष्ठा platक्रमm_device *pdev, माप_प्रकार cd_size, पूर्णांक cd_num,
	       स्थिर काष्ठा clk_bulk_data *cd);
पूर्णांक qnoc_हटाओ(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर
