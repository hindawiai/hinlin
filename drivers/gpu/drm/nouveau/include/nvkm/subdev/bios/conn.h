<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_CONN_H__
#घोषणा __NVBIOS_CONN_H__
क्रमागत dcb_connector_type अणु
	DCB_CONNECTOR_VGA = 0x00,
	DCB_CONNECTOR_TV_0 = 0x10,
	DCB_CONNECTOR_TV_1 = 0x11,
	DCB_CONNECTOR_TV_3 = 0x13,
	DCB_CONNECTOR_DVI_I = 0x30,
	DCB_CONNECTOR_DVI_D = 0x31,
	DCB_CONNECTOR_DMS59_0 = 0x38,
	DCB_CONNECTOR_DMS59_1 = 0x39,
	DCB_CONNECTOR_LVDS = 0x40,
	DCB_CONNECTOR_LVDS_SPWG = 0x41,
	DCB_CONNECTOR_DP = 0x46,
	DCB_CONNECTOR_eDP = 0x47,
	DCB_CONNECTOR_mDP = 0x48,
	DCB_CONNECTOR_HDMI_0 = 0x60,
	DCB_CONNECTOR_HDMI_1 = 0x61,
	DCB_CONNECTOR_HDMI_C = 0x63,
	DCB_CONNECTOR_DMS59_DP0 = 0x64,
	DCB_CONNECTOR_DMS59_DP1 = 0x65,
	DCB_CONNECTOR_WFD	= 0x70,
	DCB_CONNECTOR_USB_C = 0x71,
	DCB_CONNECTOR_NONE = 0xff
पूर्ण;

काष्ठा nvbios_connT अणु
पूर्ण;

u32 nvbios_connTe(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u32 nvbios_connTp(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		  काष्ठा nvbios_connT *info);

काष्ठा nvbios_connE अणु
	u8 type;
	u8 location;
	u8 hpd;
	u8 dp;
	u8 di;
	u8 sr;
	u8 lcdid;
पूर्ण;

u32 nvbios_connEe(काष्ठा nvkm_bios *bios, u8 idx, u8 *ver, u8 *hdr);
u32 nvbios_connEp(काष्ठा nvkm_bios *bios, u8 idx, u8 *ver, u8 *hdr,
		  काष्ठा nvbios_connE *info);
#पूर्ण_अगर
