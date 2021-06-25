<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
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

#अगर_अघोषित USNIC_VNIC_H_
#घोषणा USNIC_VNIC_H_

#समावेश <linux/pci.h>

#समावेश "vnic_dev.h"

/*                      =USNIC_VNIC_RES_TYPE= =VNIC_RES=   =DESC= */
#घोषणा USNIC_VNIC_RES_TYPES \
	DEFINE_USNIC_VNIC_RES_AT(EOL, RES_TYPE_EOL, "EOL", 0) \
	DEFINE_USNIC_VNIC_RES(WQ, RES_TYPE_WQ, "WQ") \
	DEFINE_USNIC_VNIC_RES(RQ, RES_TYPE_RQ, "RQ") \
	DEFINE_USNIC_VNIC_RES(CQ, RES_TYPE_CQ, "CQ") \
	DEFINE_USNIC_VNIC_RES(INTR, RES_TYPE_INTR_CTRL, "INT") \
	DEFINE_USNIC_VNIC_RES(MAX, RES_TYPE_MAX, "MAX")\

#घोषणा DEFINE_USNIC_VNIC_RES_AT(usnic_vnic_res_t, vnic_res_type, desc, val) \
	USNIC_VNIC_RES_TYPE_##usnic_vnic_res_t = val,
#घोषणा DEFINE_USNIC_VNIC_RES(usnic_vnic_res_t, vnic_res_type, desc) \
	USNIC_VNIC_RES_TYPE_##usnic_vnic_res_t,
क्रमागत usnic_vnic_res_type अणु
	USNIC_VNIC_RES_TYPES
पूर्ण;
#अघोषित DEFINE_USNIC_VNIC_RES
#अघोषित DEFINE_USNIC_VNIC_RES_AT

काष्ठा usnic_vnic_res अणु
	क्रमागत usnic_vnic_res_type	type;
	अचिन्हित पूर्णांक			vnic_idx;
	काष्ठा usnic_vnic		*vnic;
	व्योम __iomem			*ctrl;
	व्योम				*owner;
पूर्ण;

काष्ठा usnic_vnic_res_chunk अणु
	क्रमागत usnic_vnic_res_type	type;
	पूर्णांक				cnt;
	पूर्णांक				मुक्त_cnt;
	काष्ठा usnic_vnic_res		**res;
	काष्ठा usnic_vnic		*vnic;
पूर्ण;

काष्ठा usnic_vnic_res_desc अणु
	क्रमागत usnic_vnic_res_type	type;
	uपूर्णांक16_t			cnt;
पूर्ण;

काष्ठा usnic_vnic_res_spec अणु
	काष्ठा usnic_vnic_res_desc resources[USNIC_VNIC_RES_TYPE_MAX];
पूर्ण;

स्थिर अक्षर *usnic_vnic_res_type_to_str(क्रमागत usnic_vnic_res_type res_type);
स्थिर अक्षर *usnic_vnic_pci_name(काष्ठा usnic_vnic *vnic);
पूर्णांक usnic_vnic_dump(काष्ठा usnic_vnic *vnic, अक्षर *buf, पूर्णांक buf_sz,
			व्योम *hdr_obj,
			पूर्णांक (*prपूर्णांकtitle)(व्योम *, अक्षर*, पूर्णांक),
			पूर्णांक (*prपूर्णांकcols)(अक्षर *, पूर्णांक),
			पूर्णांक (*prपूर्णांकrow)(व्योम *, अक्षर *, पूर्णांक));
व्योम usnic_vnic_res_spec_update(काष्ठा usnic_vnic_res_spec *spec,
				क्रमागत usnic_vnic_res_type trgt_type,
				u16 cnt);
पूर्णांक usnic_vnic_res_spec_satisfied(स्थिर काष्ठा usnic_vnic_res_spec *min_spec,
					काष्ठा usnic_vnic_res_spec *res_spec);
पूर्णांक usnic_vnic_spec_dump(अक्षर *buf, पूर्णांक buf_sz,
				काष्ठा usnic_vnic_res_spec *res_spec);
पूर्णांक usnic_vnic_check_room(काष्ठा usnic_vnic *vnic,
				काष्ठा usnic_vnic_res_spec *res_spec);
पूर्णांक usnic_vnic_res_cnt(काष्ठा usnic_vnic *vnic,
				क्रमागत usnic_vnic_res_type type);
पूर्णांक usnic_vnic_res_मुक्त_cnt(काष्ठा usnic_vnic *vnic,
				क्रमागत usnic_vnic_res_type type);
काष्ठा usnic_vnic_res_chunk *
usnic_vnic_get_resources(काष्ठा usnic_vnic *vnic,
				क्रमागत usnic_vnic_res_type type,
				पूर्णांक cnt,
				व्योम *owner);
व्योम usnic_vnic_put_resources(काष्ठा usnic_vnic_res_chunk *chunk);
काष्ठा pci_dev *usnic_vnic_get_pdev(काष्ठा usnic_vnic *vnic);
काष्ठा vnic_dev_bar *usnic_vnic_get_bar(काष्ठा usnic_vnic *vnic,
				पूर्णांक bar_num);
काष्ठा usnic_vnic *usnic_vnic_alloc(काष्ठा pci_dev *pdev);
व्योम usnic_vnic_मुक्त(काष्ठा usnic_vnic *vnic);
u16 usnic_vnic_get_index(काष्ठा usnic_vnic *vnic);

#पूर्ण_अगर /*!USNIC_VNIC_H_*/
