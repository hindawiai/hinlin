<शैली गुरु>
/*
 * Copyright (c) 201 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _LINUX_BRCMFMAC_PLATFORM_H
#घोषणा _LINUX_BRCMFMAC_PLATFORM_H


#घोषणा BRCMFMAC_PDATA_NAME		"brcmfmac"

#घोषणा BRCMFMAC_COUNTRY_BUF_SZ		4


/*
 * Platक्रमm specअगरic driver functions and data. Through the platक्रमm specअगरic
 * device data functions and data can be provided to help the brcmfmac driver to
 * operate with the device in combination with the used platक्रमm.
 */


/**
 * Note: the brcmfmac can be loaded as module or be अटलally built-in पूर्णांकo
 * the kernel. If built-in then करो note that it uses module_init (and
 * module_निकास) routines which equal device_initcall. So अगर you पूर्णांकend to
 * create a module with the platक्रमm specअगरic data क्रम the brcmfmac and have
 * it built-in to the kernel then use a higher initcall then device_initcall
 * (see init.h). If this is not करोne then brcmfmac will load without problems
 * but will not pickup the platक्रमm data.
 *
 * When the driver करोes not "detect" platक्रमm driver data then it will जारी
 * without reporting anything and just assume there is no data needed. Which is
 * probably true क्रम most platक्रमms.
 */

/**
 * क्रमागत brcmf_bus_type - Bus type identअगरier. Currently SDIO, USB and PCIE are
 *			 supported.
 */
क्रमागत brcmf_bus_type अणु
	BRCMF_BUSTYPE_SDIO,
	BRCMF_BUSTYPE_USB,
	BRCMF_BUSTYPE_PCIE
पूर्ण;


/**
 * काष्ठा brcmfmac_sdio_pd - SDIO Device specअगरic platक्रमm data.
 *
 * @txglomsz:		SDIO txglom size. Use 0 अगर शेष of driver is to be
 *			used.
 * @drive_strength:	is the preferred drive_strength to be used क्रम the SDIO
 *			pins. If 0 then a शेष value will be used. This is
 *			the target drive strength, the exact drive strength
 *			which will be used depends on the capabilities of the
 *			device.
 * @oob_irq_supported:	करोes the board have support क्रम OOB पूर्णांकerrupts. SDIO
 *			in-band पूर्णांकerrupts are relatively slow and क्रम having
 *			less overhead on पूर्णांकerrupt processing an out of band
 *			पूर्णांकerrupt can be used. If the HW supports this then
 *			enable this by setting this field to true and configure
 *			the oob related fields.
 * @oob_irq_nr,
 * @oob_irq_flags:	the OOB पूर्णांकerrupt inक्रमmation. The values are used क्रम
 *			रेजिस्टरing the irq using request_irq function.
 * @broken_sg_support:	flag क्रम broken sg list support of SDIO host controller.
 *			Set this to true अगर the SDIO host controller has higher
 *			align requirement than 32 bytes क्रम each scatterlist
 *			item.
 * @sd_head_align:	alignment requirement क्रम start of data buffer.
 * @sd_sgentry_align:	length alignment requirement क्रम each sg entry.
 * @reset:		This function can get called अगर the device communication
 *			broke करोwn. This functionality is particularly useful in
 *			हाल of SDIO type devices. It is possible to reset a
 *			करोngle via sdio data पूर्णांकerface, but it requires that
 *			this is fully functional. This function is chip/module
 *			specअगरic and this function should वापस only after the
 *			complete reset has completed.
 */
काष्ठा brcmfmac_sdio_pd अणु
	पूर्णांक		txglomsz;
	अचिन्हित पूर्णांक	drive_strength;
	bool		oob_irq_supported;
	अचिन्हित पूर्णांक	oob_irq_nr;
	अचिन्हित दीर्घ	oob_irq_flags;
	bool		broken_sg_support;
	अचिन्हित लघु	sd_head_align;
	अचिन्हित लघु	sd_sgentry_align;
	व्योम		(*reset)(व्योम);
पूर्ण;

/**
 * काष्ठा brcmfmac_pd_cc_entry - Struct क्रम translating user space country code
 *				 (iso3166) to firmware country code and
 *				 revision.
 *
 * @iso3166:	iso3166 alpha 2 country code string.
 * @cc:		firmware country code string.
 * @rev:	firmware country code revision.
 */
काष्ठा brcmfmac_pd_cc_entry अणु
	अक्षर	iso3166[BRCMFMAC_COUNTRY_BUF_SZ];
	अक्षर	cc[BRCMFMAC_COUNTRY_BUF_SZ];
	s32	rev;
पूर्ण;

/**
 * काष्ठा brcmfmac_pd_cc - Struct क्रम translating country codes as set by user
 *			   space to a country code and rev which can be used by
 *			   firmware.
 *
 * @table_size:	number of entries in table (> 0)
 * @table:	array of 1 or more elements with translation inक्रमmation.
 */
काष्ठा brcmfmac_pd_cc अणु
	पूर्णांक				table_size;
	काष्ठा brcmfmac_pd_cc_entry	table[0];
पूर्ण;

/**
 * काष्ठा brcmfmac_pd_device - Device specअगरic platक्रमm data. (id/rev/bus_type)
 *			       is the unique identअगरier of the device.
 *
 * @id:			ID of the device क्रम which this data is. In हाल of SDIO
 *			or PCIE this is the chipid as identअगरied by chip.c In
 *			हाल of USB this is the chipid as identअगरied by the
 *			device query.
 * @rev:		chip revision, see id.
 * @bus_type:		The type of bus. Some chipid/rev exist क्रम dअगरferent bus
 *			types. Each bus type has its own set of settings.
 * @feature_disable:	Biपंचांगask of features to disable (override), See feature.c
 *			in brcmfmac क्रम details.
 * @country_codes:	If available, poपूर्णांकer to काष्ठा क्रम translating country
 *			codes.
 * @bus:		Bus specअगरic (जोड़) device settings. Currently only
 *			SDIO.
 */
काष्ठा brcmfmac_pd_device अणु
	अचिन्हित पूर्णांक		id;
	अचिन्हित पूर्णांक		rev;
	क्रमागत brcmf_bus_type	bus_type;
	अचिन्हित पूर्णांक		feature_disable;
	काष्ठा brcmfmac_pd_cc	*country_codes;
	जोड़ अणु
		काष्ठा brcmfmac_sdio_pd sdio;
	पूर्ण bus;
पूर्ण;

/**
 * काष्ठा brcmfmac_platक्रमm_data - BRCMFMAC specअगरic platक्रमm data.
 *
 * @घातer_on:	This function is called by the brcmfmac driver when the module
 *		माला_लो loaded. This can be particularly useful क्रम low घातer
 *		devices. The platक्रमm spcअगरic routine may क्रम example decide to
 *		घातer up the complete device. If there is no use-हाल क्रम this
 *		function then provide शून्य.
 * @घातer_off:	This function is called by the brcmfmac when the module माला_लो
 *		unloaded. At this poपूर्णांक the devices can be घातered करोwn or
 *		otherwise be reset. So अगर an actual घातer_off is not supported
 *		but reset is supported by the devices then reset the devices
 *		when this function माला_लो called. This can be particularly useful
 *		क्रम low घातer devices. If there is no use-हाल क्रम this
 *		function then provide शून्य.
 */
काष्ठा brcmfmac_platक्रमm_data अणु
	व्योम	(*घातer_on)(व्योम);
	व्योम	(*घातer_off)(व्योम);
	अक्षर	*fw_alternative_path;
	पूर्णांक	device_count;
	काष्ठा brcmfmac_pd_device devices[0];
पूर्ण;


#पूर्ण_अगर /* _LINUX_BRCMFMAC_PLATFORM_H */
