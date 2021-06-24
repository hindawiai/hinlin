<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Device tree helpers क्रम DMA request / controller
 *
 * Based on of_gpio.c
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>

#समावेश "dmaengine.h"

अटल LIST_HEAD(of_dma_list);
अटल DEFINE_MUTEX(of_dma_lock);

/**
 * of_dma_find_controller - Get a DMA controller in DT DMA helpers list
 * @dma_spec:	poपूर्णांकer to DMA specअगरier as found in the device tree
 *
 * Finds a DMA controller with matching device node and number क्रम dma cells
 * in a list of रेजिस्टरed DMA controllers. If a match is found a valid poपूर्णांकer
 * to the DMA data stored is retuned. A शून्य poपूर्णांकer is वापसed अगर no match is
 * found.
 */
अटल काष्ठा of_dma *of_dma_find_controller(काष्ठा of_phandle_args *dma_spec)
अणु
	काष्ठा of_dma *ofdma;

	list_क्रम_each_entry(ofdma, &of_dma_list, of_dma_controllers)
		अगर (ofdma->of_node == dma_spec->np)
			वापस ofdma;

	pr_debug("%s: can't find DMA controller %pOF\n", __func__,
		 dma_spec->np);

	वापस शून्य;
पूर्ण

/**
 * of_dma_router_xlate - translation function क्रम router devices
 * @dma_spec:	poपूर्णांकer to DMA specअगरier as found in the device tree
 * @ofdma:	poपूर्णांकer to DMA controller data (router inक्रमmation)
 *
 * The function creates new dma_spec to be passed to the router driver's
 * of_dma_route_allocate() function to prepare a dma_spec which will be used
 * to request channel from the real DMA controller.
 */
अटल काष्ठा dma_chan *of_dma_router_xlate(काष्ठा of_phandle_args *dma_spec,
					    काष्ठा of_dma *ofdma)
अणु
	काष्ठा dma_chan		*chan;
	काष्ठा of_dma		*ofdma_target;
	काष्ठा of_phandle_args	dma_spec_target;
	व्योम			*route_data;

	/* translate the request क्रम the real DMA controller */
	स_नकल(&dma_spec_target, dma_spec, माप(dma_spec_target));
	route_data = ofdma->of_dma_route_allocate(&dma_spec_target, ofdma);
	अगर (IS_ERR(route_data))
		वापस शून्य;

	ofdma_target = of_dma_find_controller(&dma_spec_target);
	अगर (!ofdma_target)
		वापस शून्य;

	chan = ofdma_target->of_dma_xlate(&dma_spec_target, ofdma_target);
	अगर (IS_ERR_OR_शून्य(chan)) अणु
		ofdma->dma_router->route_मुक्त(ofdma->dma_router->dev,
					      route_data);
	पूर्ण अन्यथा अणु
		पूर्णांक ret = 0;

		chan->router = ofdma->dma_router;
		chan->route_data = route_data;

		अगर (chan->device->device_router_config)
			ret = chan->device->device_router_config(chan);

		अगर (ret) अणु
			dma_release_channel(chan);
			chan = ERR_PTR(ret);
		पूर्ण
	पूर्ण

	/*
	 * Need to put the node back since the ofdma->of_dma_route_allocate
	 * has taken it क्रम generating the new, translated dma_spec
	 */
	of_node_put(dma_spec_target.np);
	वापस chan;
पूर्ण

/**
 * of_dma_controller_रेजिस्टर - Register a DMA controller to DT DMA helpers
 * @np:			device node of DMA controller
 * @of_dma_xlate:	translation function which converts a phandle
 *			arguments list पूर्णांकo a dma_chan काष्ठाure
 * @data:		poपूर्णांकer to controller specअगरic data to be used by
 *			translation function
 *
 * Returns 0 on success or appropriate त्रुटि_सं value on error.
 *
 * Allocated memory should be मुक्तd with appropriate of_dma_controller_मुक्त()
 * call.
 */
पूर्णांक of_dma_controller_रेजिस्टर(काष्ठा device_node *np,
				काष्ठा dma_chan *(*of_dma_xlate)
				(काष्ठा of_phandle_args *, काष्ठा of_dma *),
				व्योम *data)
अणु
	काष्ठा of_dma	*ofdma;

	अगर (!np || !of_dma_xlate) अणु
		pr_err("%s: not enough information provided\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ofdma = kzalloc(माप(*ofdma), GFP_KERNEL);
	अगर (!ofdma)
		वापस -ENOMEM;

	ofdma->of_node = np;
	ofdma->of_dma_xlate = of_dma_xlate;
	ofdma->of_dma_data = data;

	/* Now queue of_dma controller काष्ठाure in list */
	mutex_lock(&of_dma_lock);
	list_add_tail(&ofdma->of_dma_controllers, &of_dma_list);
	mutex_unlock(&of_dma_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_dma_controller_रेजिस्टर);

/**
 * of_dma_controller_मुक्त - Remove a DMA controller from DT DMA helpers list
 * @np:		device node of DMA controller
 *
 * Memory allocated by of_dma_controller_रेजिस्टर() is मुक्तd here.
 */
व्योम of_dma_controller_मुक्त(काष्ठा device_node *np)
अणु
	काष्ठा of_dma *ofdma;

	mutex_lock(&of_dma_lock);

	list_क्रम_each_entry(ofdma, &of_dma_list, of_dma_controllers)
		अगर (ofdma->of_node == np) अणु
			list_del(&ofdma->of_dma_controllers);
			kमुक्त(ofdma);
			अवरोध;
		पूर्ण

	mutex_unlock(&of_dma_lock);
पूर्ण
EXPORT_SYMBOL_GPL(of_dma_controller_मुक्त);

/**
 * of_dma_router_रेजिस्टर - Register a DMA router to DT DMA helpers as a
 *			    controller
 * @np:				device node of DMA router
 * @of_dma_route_allocate:	setup function क्रम the router which need to
 *				modअगरy the dma_spec क्रम the DMA controller to
 *				use and to set up the requested route.
 * @dma_router:			poपूर्णांकer to dma_router काष्ठाure to be used when
 *				the route need to be मुक्त up.
 *
 * Returns 0 on success or appropriate त्रुटि_सं value on error.
 *
 * Allocated memory should be मुक्तd with appropriate of_dma_controller_मुक्त()
 * call.
 */
पूर्णांक of_dma_router_रेजिस्टर(काष्ठा device_node *np,
			   व्योम *(*of_dma_route_allocate)
			   (काष्ठा of_phandle_args *, काष्ठा of_dma *),
			   काष्ठा dma_router *dma_router)
अणु
	काष्ठा of_dma	*ofdma;

	अगर (!np || !of_dma_route_allocate || !dma_router) अणु
		pr_err("%s: not enough information provided\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ofdma = kzalloc(माप(*ofdma), GFP_KERNEL);
	अगर (!ofdma)
		वापस -ENOMEM;

	ofdma->of_node = np;
	ofdma->of_dma_xlate = of_dma_router_xlate;
	ofdma->of_dma_route_allocate = of_dma_route_allocate;
	ofdma->dma_router = dma_router;

	/* Now queue of_dma controller काष्ठाure in list */
	mutex_lock(&of_dma_lock);
	list_add_tail(&ofdma->of_dma_controllers, &of_dma_list);
	mutex_unlock(&of_dma_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_dma_router_रेजिस्टर);

/**
 * of_dma_match_channel - Check अगर a DMA specअगरier matches name
 * @np:		device node to look क्रम DMA channels
 * @name:	channel name to be matched
 * @index:	index of DMA specअगरier in list of DMA specअगरiers
 * @dma_spec:	poपूर्णांकer to DMA specअगरier as found in the device tree
 *
 * Check अगर the DMA specअगरier poपूर्णांकed to by the index in a list of DMA
 * specअगरiers, matches the name provided. Returns 0 अगर the name matches and
 * a valid poपूर्णांकer to the DMA specअगरier is found. Otherwise वापसs -ENODEV.
 */
अटल पूर्णांक of_dma_match_channel(काष्ठा device_node *np, स्थिर अक्षर *name,
				पूर्णांक index, काष्ठा of_phandle_args *dma_spec)
अणु
	स्थिर अक्षर *s;

	अगर (of_property_पढ़ो_string_index(np, "dma-names", index, &s))
		वापस -ENODEV;

	अगर (म_भेद(name, s))
		वापस -ENODEV;

	अगर (of_parse_phandle_with_args(np, "dmas", "#dma-cells", index,
				       dma_spec))
		वापस -ENODEV;

	वापस 0;
पूर्ण

/**
 * of_dma_request_slave_channel - Get the DMA slave channel
 * @np:		device node to get DMA request from
 * @name:	name of desired channel
 *
 * Returns poपूर्णांकer to appropriate DMA channel on success or an error poपूर्णांकer.
 */
काष्ठा dma_chan *of_dma_request_slave_channel(काष्ठा device_node *np,
					      स्थिर अक्षर *name)
अणु
	काष्ठा of_phandle_args	dma_spec;
	काष्ठा of_dma		*ofdma;
	काष्ठा dma_chan		*chan;
	पूर्णांक			count, i, start;
	पूर्णांक			ret_no_channel = -ENODEV;
	अटल atomic_t		last_index;

	अगर (!np || !name) अणु
		pr_err("%s: not enough information provided\n", __func__);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	/* Silently fail अगर there is not even the "dmas" property */
	अगर (!of_find_property(np, "dmas", शून्य))
		वापस ERR_PTR(-ENODEV);

	count = of_property_count_strings(np, "dma-names");
	अगर (count < 0) अणु
		pr_err("%s: dma-names property of node '%pOF' missing or empty\n",
			__func__, np);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	/*
	 * approximate an average distribution across multiple
	 * entries with the same name
	 */
	start = atomic_inc_वापस(&last_index);
	क्रम (i = 0; i < count; i++) अणु
		अगर (of_dma_match_channel(np, name,
					 (i + start) % count,
					 &dma_spec))
			जारी;

		mutex_lock(&of_dma_lock);
		ofdma = of_dma_find_controller(&dma_spec);

		अगर (ofdma) अणु
			chan = ofdma->of_dma_xlate(&dma_spec, ofdma);
		पूर्ण अन्यथा अणु
			ret_no_channel = -EPROBE_DEFER;
			chan = शून्य;
		पूर्ण

		mutex_unlock(&of_dma_lock);

		of_node_put(dma_spec.np);

		अगर (chan)
			वापस chan;
	पूर्ण

	वापस ERR_PTR(ret_no_channel);
पूर्ण
EXPORT_SYMBOL_GPL(of_dma_request_slave_channel);

/**
 * of_dma_simple_xlate - Simple DMA engine translation function
 * @dma_spec:	poपूर्णांकer to DMA specअगरier as found in the device tree
 * @ofdma:	poपूर्णांकer to DMA controller data
 *
 * A simple translation function क्रम devices that use a 32-bit value क्रम the
 * filter_param when calling the DMA engine dma_request_channel() function.
 * Note that this translation function requires that #dma-cells is equal to 1
 * and the argument of the dma specअगरier is the 32-bit filter_param. Returns
 * poपूर्णांकer to appropriate dma channel on success or शून्य on error.
 */
काष्ठा dma_chan *of_dma_simple_xlate(काष्ठा of_phandle_args *dma_spec,
						काष्ठा of_dma *ofdma)
अणु
	पूर्णांक count = dma_spec->args_count;
	काष्ठा of_dma_filter_info *info = ofdma->of_dma_data;

	अगर (!info || !info->filter_fn)
		वापस शून्य;

	अगर (count != 1)
		वापस शून्य;

	वापस __dma_request_channel(&info->dma_cap, info->filter_fn,
				     &dma_spec->args[0], dma_spec->np);
पूर्ण
EXPORT_SYMBOL_GPL(of_dma_simple_xlate);

/**
 * of_dma_xlate_by_chan_id - Translate dt property to DMA channel by channel id
 * @dma_spec:	poपूर्णांकer to DMA specअगरier as found in the device tree
 * @ofdma:	poपूर्णांकer to DMA controller data
 *
 * This function can be used as the of xlate callback क्रम DMA driver which wants
 * to match the channel based on the channel id. When using this xlate function
 * the #dma-cells propety of the DMA controller dt node needs to be set to 1.
 * The data parameter of of_dma_controller_रेजिस्टर must be a poपूर्णांकer to the
 * dma_device काष्ठा the function should match upon.
 *
 * Returns poपूर्णांकer to appropriate dma channel on success or शून्य on error.
 */
काष्ठा dma_chan *of_dma_xlate_by_chan_id(काष्ठा of_phandle_args *dma_spec,
					 काष्ठा of_dma *ofdma)
अणु
	काष्ठा dma_device *dev = ofdma->of_dma_data;
	काष्ठा dma_chan *chan, *candidate = शून्य;

	अगर (!dev || dma_spec->args_count != 1)
		वापस शून्य;

	list_क्रम_each_entry(chan, &dev->channels, device_node)
		अगर (chan->chan_id == dma_spec->args[0]) अणु
			candidate = chan;
			अवरोध;
		पूर्ण

	अगर (!candidate)
		वापस शून्य;

	वापस dma_get_slave_channel(candidate);
पूर्ण
EXPORT_SYMBOL_GPL(of_dma_xlate_by_chan_id);
