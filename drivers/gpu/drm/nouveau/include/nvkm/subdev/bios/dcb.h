<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_DCB_H__
#घोषणा __NVBIOS_DCB_H__
क्रमागत dcb_output_type अणु
	DCB_OUTPUT_ANALOG	= 0x0,
	DCB_OUTPUT_TV		= 0x1,
	DCB_OUTPUT_TMDS		= 0x2,
	DCB_OUTPUT_LVDS		= 0x3,
	DCB_OUTPUT_DP		= 0x6,
	DCB_OUTPUT_WFD		= 0x8,
	DCB_OUTPUT_EOL		= 0xe,
	DCB_OUTPUT_UNUSED	= 0xf,
	DCB_OUTPUT_ANY = -1,
पूर्ण;

काष्ठा dcb_output अणु
	पूर्णांक index;	/* may not be raw dcb index अगर merging has happened */
	u16 hasht;
	u16 hashm;
	क्रमागत dcb_output_type type;
	uपूर्णांक8_t i2c_index;
	uपूर्णांक8_t heads;
	uपूर्णांक8_t connector;
	uपूर्णांक8_t bus;
	uपूर्णांक8_t location;
	uपूर्णांक8_t or;
	uपूर्णांक8_t link;
	bool duallink_possible;
	uपूर्णांक8_t extdev;
	जोड़ अणु
		काष्ठा sor_conf अणु
			पूर्णांक link;
		पूर्ण sorconf;
		काष्ठा अणु
			पूर्णांक maxfreq;
		पूर्ण crtconf;
		काष्ठा अणु
			काष्ठा sor_conf sor;
			bool use_straps_क्रम_mode;
			bool use_acpi_क्रम_edid;
			bool use_घातer_scripts;
		पूर्ण lvdsconf;
		काष्ठा अणु
			bool has_component_output;
		पूर्ण tvconf;
		काष्ठा अणु
			काष्ठा sor_conf sor;
			पूर्णांक link_nr;
			पूर्णांक link_bw;
		पूर्ण dpconf;
		काष्ठा अणु
			काष्ठा sor_conf sor;
			पूर्णांक slave_addr;
		पूर्ण पंचांगdsconf;
	पूर्ण;
	bool i2c_upper_शेष;
पूर्ण;

u16 dcb_table(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr, u8 *ent, u8 *len);
u16 dcb_outp(काष्ठा nvkm_bios *, u8 idx, u8 *ver, u8 *len);
u16 dcb_outp_parse(काष्ठा nvkm_bios *, u8 idx, u8 *, u8 *,
		   काष्ठा dcb_output *);
u16 dcb_outp_match(काष्ठा nvkm_bios *, u16 type, u16 mask, u8 *, u8 *,
		   काष्ठा dcb_output *);
पूर्णांक dcb_outp_क्रमeach(काष्ठा nvkm_bios *, व्योम *data, पूर्णांक (*exec)
		     (काष्ठा nvkm_bios *, व्योम *, पूर्णांक index, u16 entry));
#पूर्ण_अगर
