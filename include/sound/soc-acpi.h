<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 *
 * Copyright (C) 2013-15, Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __LINUX_SND_SOC_ACPI_H
#घोषणा __LINUX_SND_SOC_ACPI_H

#समावेश <linux/मानकघोष.स>
#समावेश <linux/acpi.h>
#समावेश <linux/mod_devicetable.h>

काष्ठा snd_soc_acpi_package_context अणु
	अक्षर *name;           /* package name */
	पूर्णांक length;           /* number of elements */
	काष्ठा acpi_buffer *क्रमmat;
	काष्ठा acpi_buffer *state;
	bool data_valid;
पूर्ण;

/* codec name is used in DAIs is i2c-<HID>:00 with HID being 8 अक्षरs */
#घोषणा SND_ACPI_I2C_ID_LEN (4 + ACPI_ID_LEN + 3 + 1)

#अगर IS_ENABLED(CONFIG_ACPI)
/* acpi match */
काष्ठा snd_soc_acpi_mach *
snd_soc_acpi_find_machine(काष्ठा snd_soc_acpi_mach *machines);

bool snd_soc_acpi_find_package_from_hid(स्थिर u8 hid[ACPI_ID_LEN],
				    काष्ठा snd_soc_acpi_package_context *ctx);

/* check all codecs */
काष्ठा snd_soc_acpi_mach *snd_soc_acpi_codec_list(व्योम *arg);

#अन्यथा
/* acpi match */
अटल अंतरभूत काष्ठा snd_soc_acpi_mach *
snd_soc_acpi_find_machine(काष्ठा snd_soc_acpi_mach *machines)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool
snd_soc_acpi_find_package_from_hid(स्थिर u8 hid[ACPI_ID_LEN],
				   काष्ठा snd_soc_acpi_package_context *ctx)
अणु
	वापस false;
पूर्ण

/* check all codecs */
अटल अंतरभूत काष्ठा snd_soc_acpi_mach *snd_soc_acpi_codec_list(व्योम *arg)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/**
 * snd_soc_acpi_mach_params: पूर्णांकerface क्रम machine driver configuration
 *
 * @acpi_ipc_irq_index: used क्रम BYT-CR detection
 * @platक्रमm: string used क्रम HDAudio codec support
 * @codec_mask: used क्रम HDAudio support
 * @common_hdmi_codec_drv: use commom HDAudio HDMI codec driver
 * @link_mask: links enabled on the board
 * @links: array of link _ADR descriptors, null terminated
 * @num_dai_drivers: number of elements in @dai_drivers
 * @dai_drivers: poपूर्णांकer to dai_drivers, used e.g. in nocodec mode
 */
काष्ठा snd_soc_acpi_mach_params अणु
	u32 acpi_ipc_irq_index;
	स्थिर अक्षर *platक्रमm;
	u32 codec_mask;
	u32 dmic_num;
	bool common_hdmi_codec_drv;
	u32 link_mask;
	स्थिर काष्ठा snd_soc_acpi_link_adr *links;
	u32 num_dai_drivers;
	काष्ठा snd_soc_dai_driver *dai_drivers;
पूर्ण;

/**
 * snd_soc_acpi_endpoपूर्णांक - endpoपूर्णांक descriptor
 * @num: endpoपूर्णांक number (mandatory, unique per device)
 * @aggregated: 0 (independent) or 1 (logically grouped)
 * @group_position: zero-based order (only when @aggregated is 1)
 * @group_id: platक्रमm-unique group identअगरier (only when @aggregrated is 1)
 */
काष्ठा snd_soc_acpi_endpoपूर्णांक अणु
	u8 num;
	u8 aggregated;
	u8 group_position;
	u8 group_id;
पूर्ण;

/**
 * snd_soc_acpi_adr_device - descriptor क्रम _ADR-क्रमागतerated device
 * @adr: 64 bit ACPI _ADR value
 * @num_endpoपूर्णांकs: number of endpoपूर्णांकs क्रम this device
 * @endpoपूर्णांकs: array of endpoपूर्णांकs
 * @name_prefix: string used क्रम codec controls
 */
काष्ठा snd_soc_acpi_adr_device अणु
	स्थिर u64 adr;
	स्थिर u8 num_endpoपूर्णांकs;
	स्थिर काष्ठा snd_soc_acpi_endpoपूर्णांक *endpoपूर्णांकs;
	स्थिर अक्षर *name_prefix;
पूर्ण;

/**
 * snd_soc_acpi_link_adr - ACPI-based list of _ADR क्रमागतerated devices
 * @mask: one bit set indicates the link this list applies to
 * @num_adr: ARRAY_SIZE of devices
 * @adr_d: array of devices
 *
 * The number of devices per link can be more than 1, e.g. in SoundWire
 * multi-drop configurations.
 */

काष्ठा snd_soc_acpi_link_adr अणु
	स्थिर u32 mask;
	स्थिर u32 num_adr;
	स्थिर काष्ठा snd_soc_acpi_adr_device *adr_d;
पूर्ण;

/**
 * snd_soc_acpi_mach: ACPI-based machine descriptor. Most of the fields are
 * related to the hardware, except क्रम the firmware and topology file names.
 * A platक्रमm supported by legacy and Sound Open Firmware (SOF) would expose
 * all firmware/topology related fields.
 *
 * @id: ACPI ID (usually the codec's) used to find a matching machine driver.
 * @link_mask: describes required board layout, e.g. क्रम SoundWire.
 * @links: array of link _ADR descriptors, null terminated.
 * @drv_name: machine driver name
 * @fw_filename: firmware file name. Used when SOF is not enabled.
 * @board: board name
 * @machine_quirk: poपूर्णांकer to quirk, usually based on DMI inक्रमmation when
 * ACPI ID alone is not sufficient, wrong or misleading
 * @quirk_data: data used to uniquely identअगरy a machine, usually a list of
 * audio codecs whose presence अगर checked with ACPI
 * @pdata: पूर्णांकended क्रम platक्रमm data or machine specअगरic-ops. This काष्ठाure
 *  is not स्थिरant since this field may be updated at run-समय
 * @sof_fw_filename: Sound Open Firmware file name, अगर enabled
 * @sof_tplg_filename: Sound Open Firmware topology file name, अगर enabled
 */
/* Descriptor क्रम SST ASoC machine driver */
काष्ठा snd_soc_acpi_mach अणु
	स्थिर u8 id[ACPI_ID_LEN];
	स्थिर u32 link_mask;
	स्थिर काष्ठा snd_soc_acpi_link_adr *links;
	स्थिर अक्षर *drv_name;
	स्थिर अक्षर *fw_filename;
	स्थिर अक्षर *board;
	काष्ठा snd_soc_acpi_mach * (*machine_quirk)(व्योम *arg);
	स्थिर व्योम *quirk_data;
	व्योम *pdata;
	काष्ठा snd_soc_acpi_mach_params mach_params;
	स्थिर अक्षर *sof_fw_filename;
	स्थिर अक्षर *sof_tplg_filename;
पूर्ण;

#घोषणा SND_SOC_ACPI_MAX_CODECS 3

/**
 * काष्ठा snd_soc_acpi_codecs: Structure to hold secondary codec inक्रमmation
 * apart from the matched one, this data will be passed to the quirk function
 * to match with the ACPI detected devices
 *
 * @num_codecs: number of secondary codecs used in the platक्रमm
 * @codecs: holds the codec IDs
 *
 */
काष्ठा snd_soc_acpi_codecs अणु
	पूर्णांक num_codecs;
	u8 codecs[SND_SOC_ACPI_MAX_CODECS][ACPI_ID_LEN];
पूर्ण;

अटल अंतरभूत bool snd_soc_acpi_sof_parent(काष्ठा device *dev)
अणु
	वापस dev->parent && dev->parent->driver && dev->parent->driver->name &&
		!म_भेदन(dev->parent->driver->name, "sof-audio-acpi", म_माप("sof-audio-acpi"));
पूर्ण

#पूर्ण_अगर
