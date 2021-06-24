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

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>

#समावेश "vnic_vic.h"

काष्ठा vic_provinfo *vic_provinfo_alloc(gfp_t flags, स्थिर u8 *oui,
	स्थिर u8 type)
अणु
	काष्ठा vic_provinfo *vp;

	अगर (!oui)
		वापस शून्य;

	vp = kzalloc(VIC_PROVINFO_MAX_DATA, flags);
	अगर (!vp)
		वापस शून्य;

	स_नकल(vp->oui, oui, माप(vp->oui));
	vp->type = type;
	vp->length = htonl(माप(vp->num_tlvs));

	वापस vp;
पूर्ण

व्योम vic_provinfo_मुक्त(काष्ठा vic_provinfo *vp)
अणु
	kमुक्त(vp);
पूर्ण

पूर्णांक vic_provinfo_add_tlv(काष्ठा vic_provinfo *vp, u16 type, u16 length,
	स्थिर व्योम *value)
अणु
	काष्ठा vic_provinfo_tlv *tlv;

	अगर (!vp || !value)
		वापस -EINVAL;

	अगर (ntohl(vp->length) + दुरत्व(काष्ठा vic_provinfo_tlv, value) +
		length > VIC_PROVINFO_MAX_TLV_DATA)
		वापस -ENOMEM;

	tlv = (काष्ठा vic_provinfo_tlv *)((u8 *)vp->tlv +
		ntohl(vp->length) - माप(vp->num_tlvs));

	tlv->type = htons(type);
	tlv->length = htons(length);
	स_नकल(tlv->value, value, length);

	vp->num_tlvs = htonl(ntohl(vp->num_tlvs) + 1);
	vp->length = htonl(ntohl(vp->length) +
		दुरत्व(काष्ठा vic_provinfo_tlv, value) + length);

	वापस 0;
पूर्ण

माप_प्रकार vic_provinfo_size(काष्ठा vic_provinfo *vp)
अणु
	वापस vp ?  ntohl(vp->length) + माप(*vp) - माप(vp->num_tlvs) : 0;
पूर्ण
