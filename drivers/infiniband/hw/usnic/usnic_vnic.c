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
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "usnic_ib.h"
#समावेश "vnic_resource.h"
#समावेश "usnic_log.h"
#समावेश "usnic_vnic.h"

काष्ठा usnic_vnic अणु
	काष्ठा vnic_dev			*vdev;
	काष्ठा vnic_dev_bar		bar[PCI_NUM_RESOURCES];
	काष्ठा usnic_vnic_res_chunk	chunks[USNIC_VNIC_RES_TYPE_MAX];
	spinlock_t			res_lock;
पूर्ण;

अटल क्रमागत vnic_res_type _to_vnic_res_type(क्रमागत usnic_vnic_res_type res_type)
अणु
#घोषणा DEFINE_USNIC_VNIC_RES_AT(usnic_vnic_res_t, vnic_res_type, desc, val) \
		vnic_res_type,
#घोषणा DEFINE_USNIC_VNIC_RES(usnic_vnic_res_t, vnic_res_type, desc) \
		vnic_res_type,
	अटल क्रमागत vnic_res_type usnic_vnic_type_2_vnic_type[] = अणु
						USNIC_VNIC_RES_TYPESपूर्ण;
#अघोषित DEFINE_USNIC_VNIC_RES
#अघोषित DEFINE_USNIC_VNIC_RES_AT

	अगर (res_type >= USNIC_VNIC_RES_TYPE_MAX)
		वापस RES_TYPE_MAX;

	वापस usnic_vnic_type_2_vnic_type[res_type];
पूर्ण

स्थिर अक्षर *usnic_vnic_res_type_to_str(क्रमागत usnic_vnic_res_type res_type)
अणु
#घोषणा DEFINE_USNIC_VNIC_RES_AT(usnic_vnic_res_t, vnic_res_type, desc, val) \
		desc,
#घोषणा DEFINE_USNIC_VNIC_RES(usnic_vnic_res_t, vnic_res_type, desc) \
		desc,
	अटल स्थिर अक्षर * स्थिर usnic_vnic_res_type_desc[] = अणु
						USNIC_VNIC_RES_TYPESपूर्ण;
#अघोषित DEFINE_USNIC_VNIC_RES
#अघोषित DEFINE_USNIC_VNIC_RES_AT

	अगर (res_type >= USNIC_VNIC_RES_TYPE_MAX)
		वापस "unknown";

	वापस usnic_vnic_res_type_desc[res_type];

पूर्ण

स्थिर अक्षर *usnic_vnic_pci_name(काष्ठा usnic_vnic *vnic)
अणु
	वापस pci_name(usnic_vnic_get_pdev(vnic));
पूर्ण

पूर्णांक usnic_vnic_dump(काष्ठा usnic_vnic *vnic, अक्षर *buf,
			पूर्णांक buf_sz,
			व्योम *hdr_obj,
			पूर्णांक (*prपूर्णांकtitle)(व्योम *, अक्षर*, पूर्णांक),
			पूर्णांक (*prपूर्णांकcols)(अक्षर *, पूर्णांक),
			पूर्णांक (*prपूर्णांकrow)(व्योम *, अक्षर *, पूर्णांक))
अणु
	काष्ठा usnic_vnic_res_chunk *chunk;
	काष्ठा usnic_vnic_res *res;
	काष्ठा vnic_dev_bar *bar0;
	पूर्णांक i, j, offset;

	offset = 0;
	bar0 = usnic_vnic_get_bar(vnic, 0);
	offset += scnम_लिखो(buf + offset, buf_sz - offset,
			"VF:%hu BAR0 bus_addr=%pa vaddr=0x%p size=%ld ",
			usnic_vnic_get_index(vnic),
			&bar0->bus_addr,
			bar0->vaddr, bar0->len);
	अगर (prपूर्णांकtitle)
		offset += prपूर्णांकtitle(hdr_obj, buf + offset, buf_sz - offset);
	offset += scnम_लिखो(buf + offset, buf_sz - offset, "\n");
	offset += scnम_लिखो(buf + offset, buf_sz - offset,
			"|RES\t|CTRL_PIN\t\t|IN_USE\t");
	अगर (prपूर्णांकcols)
		offset += prपूर्णांकcols(buf + offset, buf_sz - offset);
	offset += scnम_लिखो(buf + offset, buf_sz - offset, "\n");

	spin_lock(&vnic->res_lock);
	क्रम (i = 0; i < ARRAY_SIZE(vnic->chunks); i++) अणु
		chunk = &vnic->chunks[i];
		क्रम (j = 0; j < chunk->cnt; j++) अणु
			res = chunk->res[j];
			offset += scnम_लिखो(buf + offset, buf_sz - offset,
					"|%s[%u]\t|0x%p\t|%u\t",
					usnic_vnic_res_type_to_str(res->type),
					res->vnic_idx, res->ctrl, !!res->owner);
			अगर (prपूर्णांकrow) अणु
				offset += prपूर्णांकrow(res->owner, buf + offset,
							buf_sz - offset);
			पूर्ण
			offset += scnम_लिखो(buf + offset, buf_sz - offset,
						"\n");
		पूर्ण
	पूर्ण
	spin_unlock(&vnic->res_lock);
	वापस offset;
पूर्ण

व्योम usnic_vnic_res_spec_update(काष्ठा usnic_vnic_res_spec *spec,
				क्रमागत usnic_vnic_res_type trgt_type,
				u16 cnt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < USNIC_VNIC_RES_TYPE_MAX; i++) अणु
		अगर (spec->resources[i].type == trgt_type) अणु
			spec->resources[i].cnt = cnt;
			वापस;
		पूर्ण
	पूर्ण

	WARN_ON(1);
पूर्ण

पूर्णांक usnic_vnic_res_spec_satisfied(स्थिर काष्ठा usnic_vnic_res_spec *min_spec,
					काष्ठा usnic_vnic_res_spec *res_spec)
अणु
	पूर्णांक found, i, j;

	क्रम (i = 0; i < USNIC_VNIC_RES_TYPE_MAX; i++) अणु
		found = 0;

		क्रम (j = 0; j < USNIC_VNIC_RES_TYPE_MAX; j++) अणु
			अगर (res_spec->resources[i].type !=
				min_spec->resources[i].type)
				जारी;
			found = 1;
			अगर (min_spec->resources[i].cnt >
					res_spec->resources[i].cnt)
				वापस -EINVAL;
			अवरोध;
		पूर्ण

		अगर (!found)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक usnic_vnic_spec_dump(अक्षर *buf, पूर्णांक buf_sz,
				काष्ठा usnic_vnic_res_spec *res_spec)
अणु
	क्रमागत usnic_vnic_res_type res_type;
	पूर्णांक res_cnt;
	पूर्णांक i;
	पूर्णांक offset = 0;

	क्रम (i = 0; i < USNIC_VNIC_RES_TYPE_MAX; i++) अणु
		res_type = res_spec->resources[i].type;
		res_cnt = res_spec->resources[i].cnt;
		offset += scnम_लिखो(buf + offset, buf_sz - offset,
				"Res: %s Cnt: %d ",
				usnic_vnic_res_type_to_str(res_type),
				res_cnt);
	पूर्ण

	वापस offset;
पूर्ण

पूर्णांक usnic_vnic_check_room(काष्ठा usnic_vnic *vnic,
				काष्ठा usnic_vnic_res_spec *res_spec)
अणु
	पूर्णांक i;
	क्रमागत usnic_vnic_res_type res_type;
	पूर्णांक res_cnt;

	क्रम (i = 0; i < USNIC_VNIC_RES_TYPE_MAX; i++) अणु
		res_type = res_spec->resources[i].type;
		res_cnt = res_spec->resources[i].cnt;

		अगर (res_type == USNIC_VNIC_RES_TYPE_EOL)
			अवरोध;

		अगर (res_cnt > usnic_vnic_res_मुक्त_cnt(vnic, res_type))
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक usnic_vnic_res_cnt(काष्ठा usnic_vnic *vnic,
				क्रमागत usnic_vnic_res_type type)
अणु
	वापस vnic->chunks[type].cnt;
पूर्ण

पूर्णांक usnic_vnic_res_मुक्त_cnt(काष्ठा usnic_vnic *vnic,
				क्रमागत usnic_vnic_res_type type)
अणु
	वापस vnic->chunks[type].मुक्त_cnt;
पूर्ण

काष्ठा usnic_vnic_res_chunk *
usnic_vnic_get_resources(काष्ठा usnic_vnic *vnic, क्रमागत usnic_vnic_res_type type,
				पूर्णांक cnt, व्योम *owner)
अणु
	काष्ठा usnic_vnic_res_chunk *src, *ret;
	काष्ठा usnic_vnic_res *res;
	पूर्णांक i;

	अगर (usnic_vnic_res_मुक्त_cnt(vnic, type) < cnt || cnt < 0 || !owner)
		वापस ERR_PTR(-EINVAL);

	ret = kzalloc(माप(*ret), GFP_ATOMIC);
	अगर (!ret)
		वापस ERR_PTR(-ENOMEM);

	अगर (cnt > 0) अणु
		ret->res = kसुस्मृति(cnt, माप(*(ret->res)), GFP_ATOMIC);
		अगर (!ret->res) अणु
			kमुक्त(ret);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		spin_lock(&vnic->res_lock);
		src = &vnic->chunks[type];
		क्रम (i = 0; i < src->cnt && ret->cnt < cnt; i++) अणु
			res = src->res[i];
			अगर (!res->owner) अणु
				src->मुक्त_cnt--;
				res->owner = owner;
				ret->res[ret->cnt++] = res;
			पूर्ण
		पूर्ण

		spin_unlock(&vnic->res_lock);
	पूर्ण
	ret->type = type;
	ret->vnic = vnic;
	WARN_ON(ret->cnt != cnt);

	वापस ret;
पूर्ण

व्योम usnic_vnic_put_resources(काष्ठा usnic_vnic_res_chunk *chunk)
अणु

	काष्ठा usnic_vnic_res *res;
	पूर्णांक i;
	काष्ठा usnic_vnic *vnic = chunk->vnic;

	अगर (chunk->cnt > 0) अणु
		spin_lock(&vnic->res_lock);
		जबतक ((i = --chunk->cnt) >= 0) अणु
			res = chunk->res[i];
			chunk->res[i] = शून्य;
			res->owner = शून्य;
			vnic->chunks[res->type].मुक्त_cnt++;
		पूर्ण
		spin_unlock(&vnic->res_lock);
	पूर्ण

	kमुक्त(chunk->res);
	kमुक्त(chunk);
पूर्ण

u16 usnic_vnic_get_index(काष्ठा usnic_vnic *vnic)
अणु
	वापस usnic_vnic_get_pdev(vnic)->devfn - 1;
पूर्ण

अटल पूर्णांक usnic_vnic_alloc_res_chunk(काष्ठा usnic_vnic *vnic,
					क्रमागत usnic_vnic_res_type type,
					काष्ठा usnic_vnic_res_chunk *chunk)
अणु
	पूर्णांक cnt, err, i;
	काष्ठा usnic_vnic_res *res;

	cnt = vnic_dev_get_res_count(vnic->vdev, _to_vnic_res_type(type));
	अगर (cnt < 1) अणु
		usnic_err("Wrong res count with cnt %d\n", cnt);
		वापस -EINVAL;
	पूर्ण

	chunk->cnt = chunk->मुक्त_cnt = cnt;
	chunk->res = kसुस्मृति(cnt, माप(*(chunk->res)), GFP_KERNEL);
	अगर (!chunk->res)
		वापस -ENOMEM;

	क्रम (i = 0; i < cnt; i++) अणु
		res = kzalloc(माप(*res), GFP_KERNEL);
		अगर (!res) अणु
			err = -ENOMEM;
			जाओ fail;
		पूर्ण
		res->type = type;
		res->vnic_idx = i;
		res->vnic = vnic;
		res->ctrl = vnic_dev_get_res(vnic->vdev,
						_to_vnic_res_type(type), i);
		chunk->res[i] = res;
	पूर्ण

	chunk->vnic = vnic;
	वापस 0;
fail:
	क्रम (i--; i >= 0; i--)
		kमुक्त(chunk->res[i]);
	kमुक्त(chunk->res);
	वापस err;
पूर्ण

अटल व्योम usnic_vnic_मुक्त_res_chunk(काष्ठा usnic_vnic_res_chunk *chunk)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < chunk->cnt; i++)
		kमुक्त(chunk->res[i]);
	kमुक्त(chunk->res);
पूर्ण

अटल पूर्णांक usnic_vnic_discover_resources(काष्ठा pci_dev *pdev,
						काष्ठा usnic_vnic *vnic)
अणु
	क्रमागत usnic_vnic_res_type res_type;
	पूर्णांक i;
	पूर्णांक err = 0;

	क्रम (i = 0; i < ARRAY_SIZE(vnic->bar); i++) अणु
		अगर (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM))
			जारी;
		vnic->bar[i].len = pci_resource_len(pdev, i);
		vnic->bar[i].vaddr = pci_iomap(pdev, i, vnic->bar[i].len);
		अगर (!vnic->bar[i].vaddr) अणु
			usnic_err("Cannot memory-map BAR %d, aborting\n",
					i);
			err = -ENODEV;
			जाओ out_clean_bar;
		पूर्ण
		vnic->bar[i].bus_addr = pci_resource_start(pdev, i);
	पूर्ण

	vnic->vdev = vnic_dev_रेजिस्टर(शून्य, pdev, pdev, vnic->bar,
			ARRAY_SIZE(vnic->bar));
	अगर (!vnic->vdev) अणु
		usnic_err("Failed to register device %s\n",
				pci_name(pdev));
		err = -EINVAL;
		जाओ out_clean_bar;
	पूर्ण

	क्रम (res_type = USNIC_VNIC_RES_TYPE_EOL + 1;
			res_type < USNIC_VNIC_RES_TYPE_MAX; res_type++) अणु
		err = usnic_vnic_alloc_res_chunk(vnic, res_type,
						&vnic->chunks[res_type]);
		अगर (err)
			जाओ out_clean_chunks;
	पूर्ण

	वापस 0;

out_clean_chunks:
	क्रम (res_type--; res_type > USNIC_VNIC_RES_TYPE_EOL; res_type--)
		usnic_vnic_मुक्त_res_chunk(&vnic->chunks[res_type]);
	vnic_dev_unरेजिस्टर(vnic->vdev);
out_clean_bar:
	क्रम (i = 0; i < ARRAY_SIZE(vnic->bar); i++) अणु
		अगर (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM))
			जारी;
		अगर (!vnic->bar[i].vaddr)
			अवरोध;

		iounmap(vnic->bar[i].vaddr);
	पूर्ण

	वापस err;
पूर्ण

काष्ठा pci_dev *usnic_vnic_get_pdev(काष्ठा usnic_vnic *vnic)
अणु
	वापस vnic_dev_get_pdev(vnic->vdev);
पूर्ण

काष्ठा vnic_dev_bar *usnic_vnic_get_bar(काष्ठा usnic_vnic *vnic,
				पूर्णांक bar_num)
अणु
	वापस (bar_num < ARRAY_SIZE(vnic->bar)) ? &vnic->bar[bar_num] : शून्य;
पूर्ण

अटल व्योम usnic_vnic_release_resources(काष्ठा usnic_vnic *vnic)
अणु
	पूर्णांक i;
	काष्ठा pci_dev *pdev;
	क्रमागत usnic_vnic_res_type res_type;

	pdev = usnic_vnic_get_pdev(vnic);

	क्रम (res_type = USNIC_VNIC_RES_TYPE_EOL + 1;
			res_type < USNIC_VNIC_RES_TYPE_MAX; res_type++)
		usnic_vnic_मुक्त_res_chunk(&vnic->chunks[res_type]);

	vnic_dev_unरेजिस्टर(vnic->vdev);

	क्रम (i = 0; i < ARRAY_SIZE(vnic->bar); i++) अणु
		अगर (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM))
			जारी;
		iounmap(vnic->bar[i].vaddr);
	पूर्ण
पूर्ण

काष्ठा usnic_vnic *usnic_vnic_alloc(काष्ठा pci_dev *pdev)
अणु
	काष्ठा usnic_vnic *vnic;
	पूर्णांक err = 0;

	अगर (!pci_is_enabled(pdev)) अणु
		usnic_err("PCI dev %s is disabled\n", pci_name(pdev));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	vnic = kzalloc(माप(*vnic), GFP_KERNEL);
	अगर (!vnic)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&vnic->res_lock);

	err = usnic_vnic_discover_resources(pdev, vnic);
	अगर (err) अणु
		usnic_err("Failed to discover %s resources with err %d\n",
				pci_name(pdev), err);
		जाओ out_मुक्त_vnic;
	पूर्ण

	usnic_dbg("Allocated vnic for %s\n", usnic_vnic_pci_name(vnic));

	वापस vnic;

out_मुक्त_vnic:
	kमुक्त(vnic);

	वापस ERR_PTR(err);
पूर्ण

व्योम usnic_vnic_मुक्त(काष्ठा usnic_vnic *vnic)
अणु
	usnic_vnic_release_resources(vnic);
	kमुक्त(vnic);
पूर्ण
