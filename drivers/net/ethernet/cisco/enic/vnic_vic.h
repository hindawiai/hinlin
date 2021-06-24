<शैली गुरु>
/*
 * Copyright 2010 Cisco Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#अगर_अघोषित _VNIC_VIC_H_
#घोषणा _VNIC_VIC_H_

/* Note: All पूर्णांकeger fields in NETWORK byte order */

/* Note: String field lengths include null अक्षर */

#घोषणा VIC_PROVINFO_CISCO_OUI		अणु 0x00, 0x00, 0x0c पूर्ण
#घोषणा VIC_PROVINFO_GENERIC_TYPE		0x4

क्रमागत vic_generic_prov_tlv_type अणु
	VIC_GENERIC_PROV_TLV_PORT_PROखाता_NAME_STR = 0,
	VIC_GENERIC_PROV_TLV_CLIENT_MAC_ADDR = 1,
	VIC_GENERIC_PROV_TLV_CLIENT_NAME_STR = 2,
	VIC_GENERIC_PROV_TLV_CLUSTER_PORT_NAME_STR = 3,
	VIC_GENERIC_PROV_TLV_CLUSTER_PORT_UUID_STR = 4,
	VIC_GENERIC_PROV_TLV_CLUSTER_UUID_STR = 5,
	VIC_GENERIC_PROV_TLV_CLUSTER_NAME_STR = 7,
	VIC_GENERIC_PROV_TLV_HOST_UUID_STR = 8,
	VIC_GENERIC_PROV_TLV_CLIENT_UUID_STR = 9,
	VIC_GENERIC_PROV_TLV_INCARNATION_NUMBER = 10,
	VIC_GENERIC_PROV_TLV_OS_TYPE = 11,
	VIC_GENERIC_PROV_TLV_OS_VENDOR = 12,
	VIC_GENERIC_PROV_TLV_CLIENT_TYPE = 15,
पूर्ण;

क्रमागत vic_generic_prov_os_type अणु
	VIC_GENERIC_PROV_OS_TYPE_UNKNOWN = 0,
	VIC_GENERIC_PROV_OS_TYPE_ESX = 1,
	VIC_GENERIC_PROV_OS_TYPE_LINUX = 2,
	VIC_GENERIC_PROV_OS_TYPE_WINDOWS = 3,
	VIC_GENERIC_PROV_OS_TYPE_SOLARIS = 4,
पूर्ण;

काष्ठा vic_provinfo अणु
	u8 oui[3];		/* OUI of data provider */
	u8 type;		/* provider-specअगरic type */
	u32 length;		/* length of data below */
	u32 num_tlvs;		/* number of tlvs */
	काष्ठा vic_provinfo_tlv अणु
		u16 type;
		u16 length;
		u8 value[0];
	पूर्ण tlv[];
पूर्ण __packed;

#घोषणा VIC_PROVINFO_ADD_TLV(vp, tlvtype, tlvlen, data) \
	करो अणु \
		err = vic_provinfo_add_tlv(vp, tlvtype, tlvlen, data); \
		अगर (err) \
			जाओ add_tlv_failure; \
	पूर्ण जबतक (0)

#घोषणा VIC_PROVINFO_MAX_DATA		1385
#घोषणा VIC_PROVINFO_MAX_TLV_DATA (VIC_PROVINFO_MAX_DATA - \
	माप(काष्ठा vic_provinfo))

काष्ठा vic_provinfo *vic_provinfo_alloc(gfp_t flags, स्थिर u8 *oui,
	स्थिर u8 type);
व्योम vic_provinfo_मुक्त(काष्ठा vic_provinfo *vp);
पूर्णांक vic_provinfo_add_tlv(काष्ठा vic_provinfo *vp, u16 type, u16 length,
	स्थिर व्योम *value);
माप_प्रकार vic_provinfo_size(काष्ठा vic_provinfo *vp);

#पूर्ण_अगर	/* _VNIC_VIC_H_ */
