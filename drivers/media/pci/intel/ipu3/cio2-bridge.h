<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Author: Dan Scally <djrscally@gmail.com> */
#अगर_अघोषित __CIO2_BRIDGE_H
#घोषणा __CIO2_BRIDGE_H

#समावेश <linux/property.h>
#समावेश <linux/types.h>

#समावेश "ipu3-cio2.h"

#घोषणा CIO2_HID				"INT343E"
#घोषणा CIO2_MAX_LANES				4
#घोषणा MAX_NUM_LINK_FREQS			3

#घोषणा CIO2_SENSOR_CONFIG(_HID, _NR, ...)	\
	(स्थिर काष्ठा cio2_sensor_config) अणु	\
		.hid = _HID,			\
		.nr_link_freqs = _NR,		\
		.link_freqs = अणु __VA_ARGS__ पूर्ण	\
	पूर्ण

#घोषणा NODE_SENSOR(_HID, _PROPS)		\
	(स्थिर काष्ठा software_node) अणु		\
		.name = _HID,			\
		.properties = _PROPS,		\
	पूर्ण

#घोषणा NODE_PORT(_PORT, _SENSOR_NODE)		\
	(स्थिर काष्ठा software_node) अणु		\
		.name = _PORT,			\
		.parent = _SENSOR_NODE,		\
	पूर्ण

#घोषणा NODE_ENDPOINT(_EP, _PORT, _PROPS)	\
	(स्थिर काष्ठा software_node) अणु		\
		.name = _EP,			\
		.parent = _PORT,		\
		.properties = _PROPS,		\
	पूर्ण

क्रमागत cio2_sensor_swnodes अणु
	SWNODE_SENSOR_HID,
	SWNODE_SENSOR_PORT,
	SWNODE_SENSOR_ENDPOINT,
	SWNODE_CIO2_PORT,
	SWNODE_CIO2_ENDPOINT,
	SWNODE_COUNT
पूर्ण;

/* Data representation as it is in ACPI SSDB buffer */
काष्ठा cio2_sensor_ssdb अणु
	u8 version;
	u8 sku;
	u8 guid_csi2[16];
	u8 devfunction;
	u8 bus;
	u32 dphylinkenfuses;
	u32 घड़ीभाग;
	u8 link;
	u8 lanes;
	u32 csiparams[10];
	u32 maxlanespeed;
	u8 sensorcalibfileidx;
	u8 sensorcalibfileidxInMBZ[3];
	u8 romtype;
	u8 vcmtype;
	u8 platक्रमminfo;
	u8 platक्रमmsubinfo;
	u8 flash;
	u8 privacyled;
	u8 degree;
	u8 mipilinkdefined;
	u32 mclkspeed;
	u8 controllogicid;
	u8 reserved1[3];
	u8 mclkport;
	u8 reserved2[13];
पूर्ण __packed;

काष्ठा cio2_property_names अणु
	अक्षर घड़ी_frequency[16];
	अक्षर rotation[9];
	अक्षर bus_type[9];
	अक्षर data_lanes[11];
	अक्षर remote_endpoपूर्णांक[16];
	अक्षर link_frequencies[17];
पूर्ण;

काष्ठा cio2_node_names अणु
	अक्षर port[7];
	अक्षर endpoपूर्णांक[11];
	अक्षर remote_port[7];
पूर्ण;

काष्ठा cio2_sensor_config अणु
	स्थिर अक्षर *hid;
	स्थिर u8 nr_link_freqs;
	स्थिर u64 link_freqs[MAX_NUM_LINK_FREQS];
पूर्ण;

काष्ठा cio2_sensor अणु
	अक्षर name[ACPI_ID_LEN];
	काष्ठा acpi_device *adev;

	काष्ठा software_node swnodes[6];
	काष्ठा cio2_node_names node_names;

	काष्ठा cio2_sensor_ssdb ssdb;
	काष्ठा cio2_property_names prop_names;
	काष्ठा property_entry ep_properties[5];
	काष्ठा property_entry dev_properties[3];
	काष्ठा property_entry cio2_properties[3];
	काष्ठा software_node_ref_args local_ref[1];
	काष्ठा software_node_ref_args remote_ref[1];
पूर्ण;

काष्ठा cio2_bridge अणु
	अक्षर cio2_node_name[ACPI_ID_LEN];
	काष्ठा software_node cio2_hid_node;
	u32 data_lanes[4];
	अचिन्हित पूर्णांक n_sensors;
	काष्ठा cio2_sensor sensors[CIO2_NUM_PORTS];
पूर्ण;

#पूर्ण_अगर
