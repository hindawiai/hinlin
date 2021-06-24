<शैली गुरु>
/*
 *  pNFS-osd on-the-wire data काष्ठाures
 *
 *  Copyright (C) 2007 Panasas Inc. [year of first खुलाation]
 *  All rights reserved.
 *
 *  Benny Halevy <bhalevy@panasas.com>
 *  Boaz Harrosh <ooo@electrozaur.com>
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License version 2
 *  See the file COPYING included with this distribution क्रम more details.
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     करोcumentation and/or other materials provided with the distribution.
 *  3. Neither the name of the Panasas company nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#अगर_अघोषित __PNFS_OSD_XDR_H__
#घोषणा __PNFS_OSD_XDR_H__

#समावेश <linux/nfs_fs.h>

/*
 * draft-ietf-nfsv4-minorversion-22
 * draft-ietf-nfsv4-pnfs-obj-12
 */

/* Layout Structure */

क्रमागत pnfs_osd_raid_algorithm4 अणु
	PNFS_OSD_RAID_0		= 1,
	PNFS_OSD_RAID_4		= 2,
	PNFS_OSD_RAID_5		= 3,
	PNFS_OSD_RAID_PQ	= 4     /* Reed-Solomon P+Q */
पूर्ण;

/*   काष्ठा pnfs_osd_data_map4 अणु
 *       uपूर्णांक32_t                    odm_num_comps;
 *       length4                     odm_stripe_unit;
 *       uपूर्णांक32_t                    odm_group_width;
 *       uपूर्णांक32_t                    odm_group_depth;
 *       uपूर्णांक32_t                    odm_mirror_cnt;
 *       pnfs_osd_raid_algorithm4    odm_raid_algorithm;
 *   पूर्ण;
 */
काष्ठा pnfs_osd_data_map अणु
	u32	odm_num_comps;
	u64	odm_stripe_unit;
	u32	odm_group_width;
	u32	odm_group_depth;
	u32	odm_mirror_cnt;
	u32	odm_raid_algorithm;
पूर्ण;

/*   काष्ठा pnfs_osd_objid4 अणु
 *       deviceid4       oid_device_id;
 *       uपूर्णांक64_t        oid_partition_id;
 *       uपूर्णांक64_t        oid_object_id;
 *   पूर्ण;
 */
काष्ठा pnfs_osd_objid अणु
	काष्ठा nfs4_deviceid	oid_device_id;
	u64			oid_partition_id;
	u64			oid_object_id;
पूर्ण;

/* For prपूर्णांकout. I use:
 * kprपूर्णांक("dev(%llx:%llx)", _DEVID_LO(poपूर्णांकer), _DEVID_HI(poपूर्णांकer));
 * BE style
 */
#घोषणा _DEVID_LO(oid_device_id) \
	(अचिन्हित दीर्घ दीर्घ)be64_to_cpup((__be64 *)(oid_device_id)->data)

#घोषणा _DEVID_HI(oid_device_id) \
	(अचिन्हित दीर्घ दीर्घ)be64_to_cpup(((__be64 *)(oid_device_id)->data) + 1)

क्रमागत pnfs_osd_version अणु
	PNFS_OSD_MISSING              = 0,
	PNFS_OSD_VERSION_1            = 1,
	PNFS_OSD_VERSION_2            = 2
पूर्ण;

काष्ठा pnfs_osd_opaque_cred अणु
	u32 cred_len;
	व्योम *cred;
पूर्ण;

क्रमागत pnfs_osd_cap_key_sec अणु
	PNFS_OSD_CAP_KEY_SEC_NONE     = 0,
	PNFS_OSD_CAP_KEY_SEC_SSV      = 1,
पूर्ण;

/*   काष्ठा pnfs_osd_object_cred4 अणु
 *       pnfs_osd_objid4         oc_object_id;
 *       pnfs_osd_version4       oc_osd_version;
 *       pnfs_osd_cap_key_sec4   oc_cap_key_sec;
 *       opaque                  oc_capability_key<>;
 *       opaque                  oc_capability<>;
 *   पूर्ण;
 */
काष्ठा pnfs_osd_object_cred अणु
	काष्ठा pnfs_osd_objid		oc_object_id;
	u32				oc_osd_version;
	u32				oc_cap_key_sec;
	काष्ठा pnfs_osd_opaque_cred	oc_cap_key;
	काष्ठा pnfs_osd_opaque_cred	oc_cap;
पूर्ण;

/*   काष्ठा pnfs_osd_layout4 अणु
 *       pnfs_osd_data_map4      olo_map;
 *       uपूर्णांक32_t                olo_comps_index;
 *       pnfs_osd_object_cred4   olo_components<>;
 *   पूर्ण;
 */
काष्ठा pnfs_osd_layout अणु
	काष्ठा pnfs_osd_data_map	olo_map;
	u32				olo_comps_index;
	u32				olo_num_comps;
	काष्ठा pnfs_osd_object_cred	*olo_comps;
पूर्ण;

/* Device Address */
क्रमागत pnfs_osd_targetid_type अणु
	OBJ_TARGET_ANON = 1,
	OBJ_TARGET_SCSI_NAME = 2,
	OBJ_TARGET_SCSI_DEVICE_ID = 3,
पूर्ण;

/*   जोड़ pnfs_osd_targetid4 चयन (pnfs_osd_targetid_type4 oti_type) अणु
 *       हाल OBJ_TARGET_SCSI_NAME:
 *           string              oti_scsi_name<>;
 *
 *       हाल OBJ_TARGET_SCSI_DEVICE_ID:
 *           opaque              oti_scsi_device_id<>;
 *
 *       शेष:
 *           व्योम;
 *   पूर्ण;
 *
 *   जोड़ pnfs_osd_targetaddr4 चयन (bool ota_available) अणु
 *       हाल TRUE:
 *           netaddr4            ota_netaddr;
 *       हाल FALSE:
 *           व्योम;
 *   पूर्ण;
 *
 *   काष्ठा pnfs_osd_deviceaddr4 अणु
 *       pnfs_osd_targetid4      oda_targetid;
 *       pnfs_osd_targetaddr4    oda_targetaddr;
 *       uपूर्णांक64_t                oda_lun;
 *       opaque                  oda_प्रणालीid<>;
 *       pnfs_osd_object_cred4   oda_root_obj_cred;
 *       opaque                  oda_osdname<>;
 *   पूर्ण;
 */
काष्ठा pnfs_osd_targetid अणु
	u32				oti_type;
	काष्ठा nfs4_string		oti_scsi_device_id;
पूर्ण;

/*   काष्ठा netaddr4 अणु
 *       // see काष्ठा rpcb in RFC1833
 *       string r_netid<>;    // network id
 *       string r_addr<>;     // universal address
 *   पूर्ण;
 */
काष्ठा pnfs_osd_net_addr अणु
	काष्ठा nfs4_string	r_netid;
	काष्ठा nfs4_string	r_addr;
पूर्ण;

काष्ठा pnfs_osd_targetaddr अणु
	u32				ota_available;
	काष्ठा pnfs_osd_net_addr	ota_netaddr;
पूर्ण;

काष्ठा pnfs_osd_deviceaddr अणु
	काष्ठा pnfs_osd_targetid	oda_targetid;
	काष्ठा pnfs_osd_targetaddr	oda_targetaddr;
	u8				oda_lun[8];
	काष्ठा nfs4_string		oda_प्रणालीid;
	काष्ठा pnfs_osd_object_cred	oda_root_obj_cred;
	काष्ठा nfs4_string		oda_osdname;
पूर्ण;

/* LAYOUTCOMMIT: layoutupdate */

/*   जोड़ pnfs_osd_deltaspaceused4 चयन (bool dsu_valid) अणु
 *       हाल TRUE:
 *           पूर्णांक64_t     dsu_delta;
 *       हाल FALSE:
 *           व्योम;
 *   पूर्ण;
 *
 *   काष्ठा pnfs_osd_layoutupdate4 अणु
 *       pnfs_osd_deltaspaceused4    olu_delta_space_used;
 *       bool                        olu_ioerr_flag;
 *   पूर्ण;
 */
काष्ठा pnfs_osd_layoutupdate अणु
	u32	dsu_valid;
	s64	dsu_delta;
	u32	olu_ioerr_flag;
पूर्ण;

/* LAYOUTRETURN: I/O Rrror Report */

क्रमागत pnfs_osd_त्रुटि_सं अणु
	PNFS_OSD_ERR_EIO		= 1,
	PNFS_OSD_ERR_NOT_FOUND		= 2,
	PNFS_OSD_ERR_NO_SPACE		= 3,
	PNFS_OSD_ERR_BAD_CRED		= 4,
	PNFS_OSD_ERR_NO_ACCESS		= 5,
	PNFS_OSD_ERR_UNREACHABLE	= 6,
	PNFS_OSD_ERR_RESOURCE		= 7
पूर्ण;

/*   काष्ठा pnfs_osd_ioerr4 अणु
 *       pnfs_osd_objid4     oer_component;
 *       length4             oer_comp_offset;
 *       length4             oer_comp_length;
 *       bool                oer_isग_लिखो;
 *       pnfs_osd_त्रुटि_सं4     oer_त्रुटि_सं;
 *   पूर्ण;
 */
काष्ठा pnfs_osd_ioerr अणु
	काष्ठा pnfs_osd_objid	oer_component;
	u64			oer_comp_offset;
	u64			oer_comp_length;
	u32			oer_isग_लिखो;
	u32			oer_त्रुटि_सं;
पूर्ण;

/* OSD XDR Client API */
/* Layout helpers */
/* Layout decoding is करोne in two parts:
 * 1. First Call pnfs_osd_xdr_decode_layout_map to पढ़ो in only the header part
 *    of the layout. @iter members need not be initialized.
 *    Returned:
 *             @layout members are set. (@layout->olo_comps set to शून्य).
 *
 *             Zero on success, or negative error अगर passed xdr is broken.
 *
 * 2. 2nd Call pnfs_osd_xdr_decode_layout_comp() in a loop until it वापसs
 *    false, to decode the next component.
 *    Returned:
 *       true अगर there is more to decode or false अगर we are करोne or error.
 *
 * Example:
 *	काष्ठा pnfs_osd_xdr_decode_layout_iter iter;
 *	काष्ठा pnfs_osd_layout layout;
 *	काष्ठा pnfs_osd_object_cred comp;
 *	पूर्णांक status;
 *
 *	status = pnfs_osd_xdr_decode_layout_map(&layout, &iter, xdr);
 *	अगर (unlikely(status))
 *		जाओ err;
 *	जबतक(pnfs_osd_xdr_decode_layout_comp(&comp, &iter, xdr, &status)) अणु
 *		// All of @comp strings poपूर्णांक to inside the xdr_buffer
 *		// or scrach buffer. Copy them out to user memory eg.
 *		copy_single_comp(dest_comp++, &comp);
 *	पूर्ण
 *	अगर (unlikely(status))
 *		जाओ err;
 */

काष्ठा pnfs_osd_xdr_decode_layout_iter अणु
	अचिन्हित total_comps;
	अचिन्हित decoded_comps;
पूर्ण;

बाह्य पूर्णांक pnfs_osd_xdr_decode_layout_map(काष्ठा pnfs_osd_layout *layout,
	काष्ठा pnfs_osd_xdr_decode_layout_iter *iter, काष्ठा xdr_stream *xdr);

बाह्य bool pnfs_osd_xdr_decode_layout_comp(काष्ठा pnfs_osd_object_cred *comp,
	काष्ठा pnfs_osd_xdr_decode_layout_iter *iter, काष्ठा xdr_stream *xdr,
	पूर्णांक *err);

/* Device Info helpers */

/* Note: All strings inside @deviceaddr poपूर्णांक to space inside @p.
 * @p should stay valid जबतक @deviceaddr is in use.
 */
बाह्य व्योम pnfs_osd_xdr_decode_deviceaddr(
	काष्ठा pnfs_osd_deviceaddr *deviceaddr, __be32 *p);

/* layoutupdate (layout_commit) xdr helpers */
बाह्य पूर्णांक
pnfs_osd_xdr_encode_layoutupdate(काष्ठा xdr_stream *xdr,
				 काष्ठा pnfs_osd_layoutupdate *lou);

/* osd_ioerror encoding (layout_वापस) */
बाह्य __be32 *pnfs_osd_xdr_ioerr_reserve_space(काष्ठा xdr_stream *xdr);
बाह्य व्योम pnfs_osd_xdr_encode_ioerr(__be32 *p, काष्ठा pnfs_osd_ioerr *ioerr);

#पूर्ण_अगर /* __PNFS_OSD_XDR_H__ */
