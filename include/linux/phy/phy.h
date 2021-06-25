<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * phy.h -- generic phy header file
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com
 *
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#अगर_अघोषित __DRIVERS_PHY_H
#घोषणा __DRIVERS_PHY_H

#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/phy/phy-dp.h>
#समावेश <linux/phy/phy-mipi-dphy.h>

काष्ठा phy;

क्रमागत phy_mode अणु
	PHY_MODE_INVALID,
	PHY_MODE_USB_HOST,
	PHY_MODE_USB_HOST_LS,
	PHY_MODE_USB_HOST_FS,
	PHY_MODE_USB_HOST_HS,
	PHY_MODE_USB_HOST_SS,
	PHY_MODE_USB_DEVICE,
	PHY_MODE_USB_DEVICE_LS,
	PHY_MODE_USB_DEVICE_FS,
	PHY_MODE_USB_DEVICE_HS,
	PHY_MODE_USB_DEVICE_SS,
	PHY_MODE_USB_OTG,
	PHY_MODE_UFS_HS_A,
	PHY_MODE_UFS_HS_B,
	PHY_MODE_PCIE,
	PHY_MODE_ETHERNET,
	PHY_MODE_MIPI_DPHY,
	PHY_MODE_SATA,
	PHY_MODE_LVDS,
	PHY_MODE_DP
पूर्ण;

क्रमागत phy_media अणु
	PHY_MEDIA_DEFAULT,
	PHY_MEDIA_SR,
	PHY_MEDIA_DAC,
पूर्ण;

/**
 * जोड़ phy_configure_opts - Opaque generic phy configuration
 *
 * @mipi_dphy:	Configuration set applicable क्रम phys supporting
 *		the MIPI_DPHY phy mode.
 * @dp:		Configuration set applicable क्रम phys supporting
 *		the DisplayPort protocol.
 */
जोड़ phy_configure_opts अणु
	काष्ठा phy_configure_opts_mipi_dphy	mipi_dphy;
	काष्ठा phy_configure_opts_dp		dp;
पूर्ण;

/**
 * काष्ठा phy_ops - set of function poपूर्णांकers क्रम perक्रमming phy operations
 * @init: operation to be perक्रमmed क्रम initializing phy
 * @निकास: operation to be perक्रमmed जबतक निकासing
 * @घातer_on: घातering on the phy
 * @घातer_off: घातering off the phy
 * @set_mode: set the mode of the phy
 * @set_media: set the media type of the phy (optional)
 * @set_speed: set the speed of the phy (optional)
 * @reset: resetting the phy
 * @calibrate: calibrate the phy
 * @release: ops to be perक्रमmed जबतक the consumer relinquishes the PHY
 * @owner: the module owner containing the ops
 */
काष्ठा phy_ops अणु
	पूर्णांक	(*init)(काष्ठा phy *phy);
	पूर्णांक	(*निकास)(काष्ठा phy *phy);
	पूर्णांक	(*घातer_on)(काष्ठा phy *phy);
	पूर्णांक	(*घातer_off)(काष्ठा phy *phy);
	पूर्णांक	(*set_mode)(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode);
	पूर्णांक	(*set_media)(काष्ठा phy *phy, क्रमागत phy_media media);
	पूर्णांक	(*set_speed)(काष्ठा phy *phy, पूर्णांक speed);

	/**
	 * @configure:
	 *
	 * Optional.
	 *
	 * Used to change the PHY parameters. phy_init() must have
	 * been called on the phy.
	 *
	 * Returns: 0 अगर successful, an negative error code otherwise
	 */
	पूर्णांक	(*configure)(काष्ठा phy *phy, जोड़ phy_configure_opts *opts);

	/**
	 * @validate:
	 *
	 * Optional.
	 *
	 * Used to check that the current set of parameters can be
	 * handled by the phy. Implementations are मुक्त to tune the
	 * parameters passed as arguments अगर needed by some
	 * implementation detail or स्थिरraपूर्णांकs. It must not change
	 * any actual configuration of the PHY, so calling it as many
	 * बार as deemed fit by the consumer must have no side
	 * effect.
	 *
	 * Returns: 0 अगर the configuration can be applied, an negative
	 * error code otherwise
	 */
	पूर्णांक	(*validate)(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode,
			    जोड़ phy_configure_opts *opts);
	पूर्णांक	(*reset)(काष्ठा phy *phy);
	पूर्णांक	(*calibrate)(काष्ठा phy *phy);
	व्योम	(*release)(काष्ठा phy *phy);
	काष्ठा module *owner;
पूर्ण;

/**
 * काष्ठा phy_attrs - represents phy attributes
 * @bus_width: Data path width implemented by PHY
 * @max_link_rate: Maximum link rate supported by PHY (in Mbps)
 * @mode: PHY mode
 */
काष्ठा phy_attrs अणु
	u32			bus_width;
	u32			max_link_rate;
	क्रमागत phy_mode		mode;
पूर्ण;

/**
 * काष्ठा phy - represents the phy device
 * @dev: phy device
 * @id: id of the phy device
 * @ops: function poपूर्णांकers क्रम perक्रमming phy operations
 * @mutex: mutex to protect phy_ops
 * @init_count: used to protect when the PHY is used by multiple consumers
 * @घातer_count: used to protect when the PHY is used by multiple consumers
 * @attrs: used to specअगरy PHY specअगरic attributes
 * @pwr: घातer regulator associated with the phy
 */
काष्ठा phy अणु
	काष्ठा device		dev;
	पूर्णांक			id;
	स्थिर काष्ठा phy_ops	*ops;
	काष्ठा mutex		mutex;
	पूर्णांक			init_count;
	पूर्णांक			घातer_count;
	काष्ठा phy_attrs	attrs;
	काष्ठा regulator	*pwr;
पूर्ण;

/**
 * काष्ठा phy_provider - represents the phy provider
 * @dev: phy provider device
 * @children: can be used to override the शेष (dev->of_node) child node
 * @owner: the module owner having of_xlate
 * @list: to मुख्यtain a linked list of PHY providers
 * @of_xlate: function poपूर्णांकer to obtain phy instance from phy poपूर्णांकer
 */
काष्ठा phy_provider अणु
	काष्ठा device		*dev;
	काष्ठा device_node	*children;
	काष्ठा module		*owner;
	काष्ठा list_head	list;
	काष्ठा phy * (*of_xlate)(काष्ठा device *dev,
		काष्ठा of_phandle_args *args);
पूर्ण;

/**
 * काष्ठा phy_lookup - PHY association in list of phys managed by the phy driver
 * @node: list node
 * @dev_id: the device of the association
 * @con_id: connection ID string on device
 * @phy: the phy of the association
 */
काष्ठा phy_lookup अणु
	काष्ठा list_head node;
	स्थिर अक्षर *dev_id;
	स्थिर अक्षर *con_id;
	काष्ठा phy *phy;
पूर्ण;

#घोषणा	to_phy(a)	(container_of((a), काष्ठा phy, dev))

#घोषणा	of_phy_provider_रेजिस्टर(dev, xlate)	\
	__of_phy_provider_रेजिस्टर((dev), शून्य, THIS_MODULE, (xlate))

#घोषणा	devm_of_phy_provider_रेजिस्टर(dev, xlate)	\
	__devm_of_phy_provider_रेजिस्टर((dev), शून्य, THIS_MODULE, (xlate))

#घोषणा of_phy_provider_रेजिस्टर_full(dev, children, xlate) \
	__of_phy_provider_रेजिस्टर(dev, children, THIS_MODULE, xlate)

#घोषणा devm_of_phy_provider_रेजिस्टर_full(dev, children, xlate) \
	__devm_of_phy_provider_रेजिस्टर(dev, children, THIS_MODULE, xlate)

अटल अंतरभूत व्योम phy_set_drvdata(काष्ठा phy *phy, व्योम *data)
अणु
	dev_set_drvdata(&phy->dev, data);
पूर्ण

अटल अंतरभूत व्योम *phy_get_drvdata(काष्ठा phy *phy)
अणु
	वापस dev_get_drvdata(&phy->dev);
पूर्ण

#अगर IS_ENABLED(CONFIG_GENERIC_PHY)
पूर्णांक phy_pm_runसमय_get(काष्ठा phy *phy);
पूर्णांक phy_pm_runसमय_get_sync(काष्ठा phy *phy);
पूर्णांक phy_pm_runसमय_put(काष्ठा phy *phy);
पूर्णांक phy_pm_runसमय_put_sync(काष्ठा phy *phy);
व्योम phy_pm_runसमय_allow(काष्ठा phy *phy);
व्योम phy_pm_runसमय_क्रमbid(काष्ठा phy *phy);
पूर्णांक phy_init(काष्ठा phy *phy);
पूर्णांक phy_निकास(काष्ठा phy *phy);
पूर्णांक phy_घातer_on(काष्ठा phy *phy);
पूर्णांक phy_घातer_off(काष्ठा phy *phy);
पूर्णांक phy_set_mode_ext(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode);
#घोषणा phy_set_mode(phy, mode) \
	phy_set_mode_ext(phy, mode, 0)
पूर्णांक phy_set_media(काष्ठा phy *phy, क्रमागत phy_media media);
पूर्णांक phy_set_speed(काष्ठा phy *phy, पूर्णांक speed);
पूर्णांक phy_configure(काष्ठा phy *phy, जोड़ phy_configure_opts *opts);
पूर्णांक phy_validate(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode,
		 जोड़ phy_configure_opts *opts);

अटल अंतरभूत क्रमागत phy_mode phy_get_mode(काष्ठा phy *phy)
अणु
	वापस phy->attrs.mode;
पूर्ण
पूर्णांक phy_reset(काष्ठा phy *phy);
पूर्णांक phy_calibrate(काष्ठा phy *phy);
अटल अंतरभूत पूर्णांक phy_get_bus_width(काष्ठा phy *phy)
अणु
	वापस phy->attrs.bus_width;
पूर्ण
अटल अंतरभूत व्योम phy_set_bus_width(काष्ठा phy *phy, पूर्णांक bus_width)
अणु
	phy->attrs.bus_width = bus_width;
पूर्ण
काष्ठा phy *phy_get(काष्ठा device *dev, स्थिर अक्षर *string);
काष्ठा phy *phy_optional_get(काष्ठा device *dev, स्थिर अक्षर *string);
काष्ठा phy *devm_phy_get(काष्ठा device *dev, स्थिर अक्षर *string);
काष्ठा phy *devm_phy_optional_get(काष्ठा device *dev, स्थिर अक्षर *string);
काष्ठा phy *devm_of_phy_get(काष्ठा device *dev, काष्ठा device_node *np,
			    स्थिर अक्षर *con_id);
काष्ठा phy *devm_of_phy_get_by_index(काष्ठा device *dev, काष्ठा device_node *np,
				     पूर्णांक index);
व्योम of_phy_put(काष्ठा phy *phy);
व्योम phy_put(काष्ठा device *dev, काष्ठा phy *phy);
व्योम devm_phy_put(काष्ठा device *dev, काष्ठा phy *phy);
काष्ठा phy *of_phy_get(काष्ठा device_node *np, स्थिर अक्षर *con_id);
काष्ठा phy *of_phy_simple_xlate(काष्ठा device *dev,
	काष्ठा of_phandle_args *args);
काष्ठा phy *phy_create(काष्ठा device *dev, काष्ठा device_node *node,
		       स्थिर काष्ठा phy_ops *ops);
काष्ठा phy *devm_phy_create(काष्ठा device *dev, काष्ठा device_node *node,
			    स्थिर काष्ठा phy_ops *ops);
व्योम phy_destroy(काष्ठा phy *phy);
व्योम devm_phy_destroy(काष्ठा device *dev, काष्ठा phy *phy);
काष्ठा phy_provider *__of_phy_provider_रेजिस्टर(काष्ठा device *dev,
	काष्ठा device_node *children, काष्ठा module *owner,
	काष्ठा phy * (*of_xlate)(काष्ठा device *dev,
				 काष्ठा of_phandle_args *args));
काष्ठा phy_provider *__devm_of_phy_provider_रेजिस्टर(काष्ठा device *dev,
	काष्ठा device_node *children, काष्ठा module *owner,
	काष्ठा phy * (*of_xlate)(काष्ठा device *dev,
				 काष्ठा of_phandle_args *args));
व्योम of_phy_provider_unरेजिस्टर(काष्ठा phy_provider *phy_provider);
व्योम devm_of_phy_provider_unरेजिस्टर(काष्ठा device *dev,
	काष्ठा phy_provider *phy_provider);
पूर्णांक phy_create_lookup(काष्ठा phy *phy, स्थिर अक्षर *con_id, स्थिर अक्षर *dev_id);
व्योम phy_हटाओ_lookup(काष्ठा phy *phy, स्थिर अक्षर *con_id, स्थिर अक्षर *dev_id);
#अन्यथा
अटल अंतरभूत पूर्णांक phy_pm_runसमय_get(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक phy_pm_runसमय_get_sync(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक phy_pm_runसमय_put(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक phy_pm_runसमय_put_sync(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम phy_pm_runसमय_allow(काष्ठा phy *phy)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम phy_pm_runसमय_क्रमbid(काष्ठा phy *phy)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक phy_init(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक phy_निकास(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक phy_घातer_on(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक phy_घातer_off(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक phy_set_mode_ext(काष्ठा phy *phy, क्रमागत phy_mode mode,
				   पूर्णांक submode)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENOSYS;
पूर्ण

#घोषणा phy_set_mode(phy, mode) \
	phy_set_mode_ext(phy, mode, 0)

अटल अंतरभूत पूर्णांक phy_set_media(काष्ठा phy *phy, क्रमागत phy_media media)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक phy_set_speed(काष्ठा phy *phy, पूर्णांक speed)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत क्रमागत phy_mode phy_get_mode(काष्ठा phy *phy)
अणु
	वापस PHY_MODE_INVALID;
पूर्ण

अटल अंतरभूत पूर्णांक phy_reset(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक phy_calibrate(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक phy_configure(काष्ठा phy *phy,
				जोड़ phy_configure_opts *opts)
अणु
	अगर (!phy)
		वापस 0;

	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक phy_validate(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode,
			       जोड़ phy_configure_opts *opts)
अणु
	अगर (!phy)
		वापस 0;

	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक phy_get_bus_width(काष्ठा phy *phy)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम phy_set_bus_width(काष्ठा phy *phy, पूर्णांक bus_width)
अणु
	वापस;
पूर्ण

अटल अंतरभूत काष्ठा phy *phy_get(काष्ठा device *dev, स्थिर अक्षर *string)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा phy *phy_optional_get(काष्ठा device *dev,
					   स्थिर अक्षर *string)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा phy *devm_phy_get(काष्ठा device *dev, स्थिर अक्षर *string)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा phy *devm_phy_optional_get(काष्ठा device *dev,
						स्थिर अक्षर *string)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा phy *devm_of_phy_get(काष्ठा device *dev,
					  काष्ठा device_node *np,
					  स्थिर अक्षर *con_id)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा phy *devm_of_phy_get_by_index(काष्ठा device *dev,
						   काष्ठा device_node *np,
						   पूर्णांक index)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत व्योम of_phy_put(काष्ठा phy *phy)
अणु
पूर्ण

अटल अंतरभूत व्योम phy_put(काष्ठा device *dev, काष्ठा phy *phy)
अणु
पूर्ण

अटल अंतरभूत व्योम devm_phy_put(काष्ठा device *dev, काष्ठा phy *phy)
अणु
पूर्ण

अटल अंतरभूत काष्ठा phy *of_phy_get(काष्ठा device_node *np, स्थिर अक्षर *con_id)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा phy *of_phy_simple_xlate(काष्ठा device *dev,
	काष्ठा of_phandle_args *args)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा phy *phy_create(काष्ठा device *dev,
				     काष्ठा device_node *node,
				     स्थिर काष्ठा phy_ops *ops)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा phy *devm_phy_create(काष्ठा device *dev,
					  काष्ठा device_node *node,
					  स्थिर काष्ठा phy_ops *ops)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत व्योम phy_destroy(काष्ठा phy *phy)
अणु
पूर्ण

अटल अंतरभूत व्योम devm_phy_destroy(काष्ठा device *dev, काष्ठा phy *phy)
अणु
पूर्ण

अटल अंतरभूत काष्ठा phy_provider *__of_phy_provider_रेजिस्टर(
	काष्ठा device *dev, काष्ठा device_node *children, काष्ठा module *owner,
	काष्ठा phy * (*of_xlate)(काष्ठा device *dev,
				 काष्ठा of_phandle_args *args))
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत काष्ठा phy_provider *__devm_of_phy_provider_रेजिस्टर(काष्ठा device
	*dev, काष्ठा device_node *children, काष्ठा module *owner,
	काष्ठा phy * (*of_xlate)(काष्ठा device *dev,
				 काष्ठा of_phandle_args *args))
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत व्योम of_phy_provider_unरेजिस्टर(काष्ठा phy_provider *phy_provider)
अणु
पूर्ण

अटल अंतरभूत व्योम devm_of_phy_provider_unरेजिस्टर(काष्ठा device *dev,
	काष्ठा phy_provider *phy_provider)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक
phy_create_lookup(काष्ठा phy *phy, स्थिर अक्षर *con_id, स्थिर अक्षर *dev_id)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम phy_हटाओ_lookup(काष्ठा phy *phy, स्थिर अक्षर *con_id,
				     स्थिर अक्षर *dev_id) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __DRIVERS_PHY_H */
