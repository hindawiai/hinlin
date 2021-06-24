<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SOUND_FIREWIRE_FCP_H_INCLUDED
#घोषणा SOUND_FIREWIRE_FCP_H_INCLUDED

#घोषणा	AVC_PLUG_INFO_BUF_BYTES	4

काष्ठा fw_unit;

/*
 * AV/C Digital Interface Command Set General Specअगरication 4.2
 * (Sep 2004, 1394TA)
 */
क्रमागत avc_general_plug_dir अणु
	AVC_GENERAL_PLUG_सूची_IN		= 0,
	AVC_GENERAL_PLUG_सूची_OUT	= 1,
	AVC_GENERAL_PLUG_सूची_COUNT
पूर्ण;
पूर्णांक avc_general_set_sig_fmt(काष्ठा fw_unit *unit, अचिन्हित पूर्णांक rate,
			    क्रमागत avc_general_plug_dir dir,
			    अचिन्हित लघु plug);
पूर्णांक avc_general_get_sig_fmt(काष्ठा fw_unit *unit, अचिन्हित पूर्णांक *rate,
			    क्रमागत avc_general_plug_dir dir,
			    अचिन्हित लघु plug);
पूर्णांक avc_general_get_plug_info(काष्ठा fw_unit *unit, अचिन्हित पूर्णांक subunit_type,
			      अचिन्हित पूर्णांक subunit_id, अचिन्हित पूर्णांक subfunction,
			      u8 info[AVC_PLUG_INFO_BUF_BYTES]);

पूर्णांक fcp_avc_transaction(काष्ठा fw_unit *unit,
			स्थिर व्योम *command, अचिन्हित पूर्णांक command_size,
			व्योम *response, अचिन्हित पूर्णांक response_size,
			अचिन्हित पूर्णांक response_match_bytes);
व्योम fcp_bus_reset(काष्ठा fw_unit *unit);

#पूर्ण_अगर
