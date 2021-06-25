<शैली गुरु>
/*
 * Copyright (c) 2016 Citrix Systems Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Softare Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#घोषणा XEN_NETIF_DEFINE_TOEPLITZ

#समावेश "common.h"
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/rculist.h>

अटल व्योम xenvअगर_add_hash(काष्ठा xenvअगर *vअगर, स्थिर u8 *tag,
			    अचिन्हित पूर्णांक len, u32 val)
अणु
	काष्ठा xenvअगर_hash_cache_entry *new, *entry, *oldest;
	अचिन्हित दीर्घ flags;
	bool found;

	new = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
	अगर (!new)
		वापस;

	स_नकल(new->tag, tag, len);
	new->len = len;
	new->val = val;

	spin_lock_irqsave(&vअगर->hash.cache.lock, flags);

	found = false;
	oldest = शून्य;
	list_क्रम_each_entry_rcu(entry, &vअगर->hash.cache.list, link,
				lockdep_is_held(&vअगर->hash.cache.lock)) अणु
		/* Make sure we करोn't add duplicate entries */
		अगर (entry->len == len &&
		    स_भेद(entry->tag, tag, len) == 0)
			found = true;
		अगर (!oldest || entry->seq < oldest->seq)
			oldest = entry;
	पूर्ण

	अगर (!found) अणु
		new->seq = atomic_inc_वापस(&vअगर->hash.cache.seq);
		list_add_rcu(&new->link, &vअगर->hash.cache.list);

		अगर (++vअगर->hash.cache.count > xenvअगर_hash_cache_size) अणु
			list_del_rcu(&oldest->link);
			vअगर->hash.cache.count--;
			kमुक्त_rcu(oldest, rcu);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&vअगर->hash.cache.lock, flags);

	अगर (found)
		kमुक्त(new);
पूर्ण

अटल u32 xenvअगर_new_hash(काष्ठा xenvअगर *vअगर, स्थिर u8 *data,
			   अचिन्हित पूर्णांक len)
अणु
	u32 val;

	val = xen_netअगर_toeplitz_hash(vअगर->hash.key,
				      माप(vअगर->hash.key),
				      data, len);

	अगर (xenvअगर_hash_cache_size != 0)
		xenvअगर_add_hash(vअगर, data, len, val);

	वापस val;
पूर्ण

अटल व्योम xenvअगर_flush_hash(काष्ठा xenvअगर *vअगर)
अणु
	काष्ठा xenvअगर_hash_cache_entry *entry;
	अचिन्हित दीर्घ flags;

	अगर (xenvअगर_hash_cache_size == 0)
		वापस;

	spin_lock_irqsave(&vअगर->hash.cache.lock, flags);

	list_क्रम_each_entry_rcu(entry, &vअगर->hash.cache.list, link,
				lockdep_is_held(&vअगर->hash.cache.lock)) अणु
		list_del_rcu(&entry->link);
		vअगर->hash.cache.count--;
		kमुक्त_rcu(entry, rcu);
	पूर्ण

	spin_unlock_irqrestore(&vअगर->hash.cache.lock, flags);
पूर्ण

अटल u32 xenvअगर_find_hash(काष्ठा xenvअगर *vअगर, स्थिर u8 *data,
			    अचिन्हित पूर्णांक len)
अणु
	काष्ठा xenvअगर_hash_cache_entry *entry;
	u32 val;
	bool found;

	अगर (len >= XEN_NETBK_HASH_TAG_SIZE)
		वापस 0;

	अगर (xenvअगर_hash_cache_size == 0)
		वापस xenvअगर_new_hash(vअगर, data, len);

	rcu_पढ़ो_lock();

	found = false;

	list_क्रम_each_entry_rcu(entry, &vअगर->hash.cache.list, link) अणु
		अगर (entry->len == len &&
		    स_भेद(entry->tag, data, len) == 0) अणु
			val = entry->val;
			entry->seq = atomic_inc_वापस(&vअगर->hash.cache.seq);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (!found)
		val = xenvअगर_new_hash(vअगर, data, len);

	वापस val;
पूर्ण

व्योम xenvअगर_set_skb_hash(काष्ठा xenvअगर *vअगर, काष्ठा sk_buff *skb)
अणु
	काष्ठा flow_keys flow;
	u32 hash = 0;
	क्रमागत pkt_hash_types type = PKT_HASH_TYPE_NONE;
	u32 flags = vअगर->hash.flags;
	bool has_tcp_hdr;

	/* Quick rejection test: If the network protocol करोesn't
	 * correspond to any enabled hash type then there's no poपूर्णांक
	 * in parsing the packet header.
	 */
	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		अगर (flags & (XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP |
			     XEN_NETIF_CTRL_HASH_TYPE_IPV4))
			अवरोध;

		जाओ करोne;

	हाल htons(ETH_P_IPV6):
		अगर (flags & (XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP |
			     XEN_NETIF_CTRL_HASH_TYPE_IPV6))
			अवरोध;

		जाओ करोne;

	शेष:
		जाओ करोne;
	पूर्ण

	स_रखो(&flow, 0, माप(flow));
	अगर (!skb_flow_dissect_flow_keys(skb, &flow, 0))
		जाओ करोne;

	has_tcp_hdr = (flow.basic.ip_proto == IPPROTO_TCP) &&
		      !(flow.control.flags & FLOW_DIS_IS_FRAGMENT);

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		अगर (has_tcp_hdr &&
		    (flags & XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP)) अणु
			u8 data[12];

			स_नकल(&data[0], &flow.addrs.v4addrs.src, 4);
			स_नकल(&data[4], &flow.addrs.v4addrs.dst, 4);
			स_नकल(&data[8], &flow.ports.src, 2);
			स_नकल(&data[10], &flow.ports.dst, 2);

			hash = xenvअगर_find_hash(vअगर, data, माप(data));
			type = PKT_HASH_TYPE_L4;
		पूर्ण अन्यथा अगर (flags & XEN_NETIF_CTRL_HASH_TYPE_IPV4) अणु
			u8 data[8];

			स_नकल(&data[0], &flow.addrs.v4addrs.src, 4);
			स_नकल(&data[4], &flow.addrs.v4addrs.dst, 4);

			hash = xenvअगर_find_hash(vअगर, data, माप(data));
			type = PKT_HASH_TYPE_L3;
		पूर्ण

		अवरोध;

	हाल htons(ETH_P_IPV6):
		अगर (has_tcp_hdr &&
		    (flags & XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP)) अणु
			u8 data[36];

			स_नकल(&data[0], &flow.addrs.v6addrs.src, 16);
			स_नकल(&data[16], &flow.addrs.v6addrs.dst, 16);
			स_नकल(&data[32], &flow.ports.src, 2);
			स_नकल(&data[34], &flow.ports.dst, 2);

			hash = xenvअगर_find_hash(vअगर, data, माप(data));
			type = PKT_HASH_TYPE_L4;
		पूर्ण अन्यथा अगर (flags & XEN_NETIF_CTRL_HASH_TYPE_IPV6) अणु
			u8 data[32];

			स_नकल(&data[0], &flow.addrs.v6addrs.src, 16);
			स_नकल(&data[16], &flow.addrs.v6addrs.dst, 16);

			hash = xenvअगर_find_hash(vअगर, data, माप(data));
			type = PKT_HASH_TYPE_L3;
		पूर्ण

		अवरोध;
	पूर्ण

करोne:
	अगर (type == PKT_HASH_TYPE_NONE)
		skb_clear_hash(skb);
	अन्यथा
		__skb_set_sw_hash(skb, hash, type == PKT_HASH_TYPE_L4);
पूर्ण

u32 xenvअगर_set_hash_alg(काष्ठा xenvअगर *vअगर, u32 alg)
अणु
	चयन (alg) अणु
	हाल XEN_NETIF_CTRL_HASH_ALGORITHM_NONE:
	हाल XEN_NETIF_CTRL_HASH_ALGORITHM_TOEPLITZ:
		अवरोध;

	शेष:
		वापस XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;
	पूर्ण

	vअगर->hash.alg = alg;

	वापस XEN_NETIF_CTRL_STATUS_SUCCESS;
पूर्ण

u32 xenvअगर_get_hash_flags(काष्ठा xenvअगर *vअगर, u32 *flags)
अणु
	अगर (vअगर->hash.alg == XEN_NETIF_CTRL_HASH_ALGORITHM_NONE)
		वापस XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED;

	*flags = XEN_NETIF_CTRL_HASH_TYPE_IPV4 |
		 XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP |
		 XEN_NETIF_CTRL_HASH_TYPE_IPV6 |
		 XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP;

	वापस XEN_NETIF_CTRL_STATUS_SUCCESS;
पूर्ण

u32 xenvअगर_set_hash_flags(काष्ठा xenvअगर *vअगर, u32 flags)
अणु
	अगर (flags & ~(XEN_NETIF_CTRL_HASH_TYPE_IPV4 |
		      XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP |
		      XEN_NETIF_CTRL_HASH_TYPE_IPV6 |
		      XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP))
		वापस XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;

	अगर (vअगर->hash.alg == XEN_NETIF_CTRL_HASH_ALGORITHM_NONE)
		वापस XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;

	vअगर->hash.flags = flags;

	वापस XEN_NETIF_CTRL_STATUS_SUCCESS;
पूर्ण

u32 xenvअगर_set_hash_key(काष्ठा xenvअगर *vअगर, u32 gref, u32 len)
अणु
	u8 *key = vअगर->hash.key;
	काष्ठा gnttab_copy copy_op = अणु
		.source.u.ref = gref,
		.source.करोmid = vअगर->करोmid,
		.dest.u.gmfn = virt_to_gfn(key),
		.dest.करोmid = DOMID_SELF,
		.dest.offset = xen_offset_in_page(key),
		.len = len,
		.flags = GNTCOPY_source_gref
	पूर्ण;

	अगर (len > XEN_NETBK_MAX_HASH_KEY_SIZE)
		वापस XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;

	अगर (copy_op.len != 0) अणु
		gnttab_batch_copy(&copy_op, 1);

		अगर (copy_op.status != GNTST_okay)
			वापस XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;
	पूर्ण

	/* Clear any reमुख्यing key octets */
	अगर (len < XEN_NETBK_MAX_HASH_KEY_SIZE)
		स_रखो(key + len, 0, XEN_NETBK_MAX_HASH_KEY_SIZE - len);

	xenvअगर_flush_hash(vअगर);

	वापस XEN_NETIF_CTRL_STATUS_SUCCESS;
पूर्ण

u32 xenvअगर_set_hash_mapping_size(काष्ठा xenvअगर *vअगर, u32 size)
अणु
	अगर (size > XEN_NETBK_MAX_HASH_MAPPING_SIZE)
		वापस XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;

	vअगर->hash.size = size;
	स_रखो(vअगर->hash.mapping[vअगर->hash.mapping_sel], 0,
	       माप(u32) * size);

	वापस XEN_NETIF_CTRL_STATUS_SUCCESS;
पूर्ण

u32 xenvअगर_set_hash_mapping(काष्ठा xenvअगर *vअगर, u32 gref, u32 len,
			    u32 off)
अणु
	u32 *mapping = vअगर->hash.mapping[!vअगर->hash.mapping_sel];
	अचिन्हित पूर्णांक nr = 1;
	काष्ठा gnttab_copy copy_op[2] = अणुअणु
		.source.u.ref = gref,
		.source.करोmid = vअगर->करोmid,
		.dest.करोmid = DOMID_SELF,
		.len = len * माप(*mapping),
		.flags = GNTCOPY_source_gref
	पूर्णपूर्ण;

	अगर ((off + len < off) || (off + len > vअगर->hash.size) ||
	    len > XEN_PAGE_SIZE / माप(*mapping))
		वापस XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;

	copy_op[0].dest.u.gmfn = virt_to_gfn(mapping + off);
	copy_op[0].dest.offset = xen_offset_in_page(mapping + off);
	अगर (copy_op[0].dest.offset + copy_op[0].len > XEN_PAGE_SIZE) अणु
		copy_op[1] = copy_op[0];
		copy_op[1].source.offset = XEN_PAGE_SIZE - copy_op[0].dest.offset;
		copy_op[1].dest.u.gmfn = virt_to_gfn(mapping + off + len);
		copy_op[1].dest.offset = 0;
		copy_op[1].len = copy_op[0].len - copy_op[1].source.offset;
		copy_op[0].len = copy_op[1].source.offset;
		nr = 2;
	पूर्ण

	स_नकल(mapping, vअगर->hash.mapping[vअगर->hash.mapping_sel],
	       vअगर->hash.size * माप(*mapping));

	अगर (copy_op[0].len != 0) अणु
		gnttab_batch_copy(copy_op, nr);

		अगर (copy_op[0].status != GNTST_okay ||
		    copy_op[nr - 1].status != GNTST_okay)
			वापस XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;
	पूर्ण

	जबतक (len-- != 0)
		अगर (mapping[off++] >= vअगर->num_queues)
			वापस XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;

	vअगर->hash.mapping_sel = !vअगर->hash.mapping_sel;

	वापस XEN_NETIF_CTRL_STATUS_SUCCESS;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
व्योम xenvअगर_dump_hash_info(काष्ठा xenvअगर *vअगर, काष्ठा seq_file *m)
अणु
	अचिन्हित पूर्णांक i;

	चयन (vअगर->hash.alg) अणु
	हाल XEN_NETIF_CTRL_HASH_ALGORITHM_TOEPLITZ:
		seq_माला_दो(m, "Hash Algorithm: TOEPLITZ\n");
		अवरोध;

	हाल XEN_NETIF_CTRL_HASH_ALGORITHM_NONE:
		seq_माला_दो(m, "Hash Algorithm: NONE\n");
		fallthrough;
	शेष:
		वापस;
	पूर्ण

	अगर (vअगर->hash.flags) अणु
		seq_माला_दो(m, "\nHash Flags:\n");

		अगर (vअगर->hash.flags & XEN_NETIF_CTRL_HASH_TYPE_IPV4)
			seq_माला_दो(m, "- IPv4\n");
		अगर (vअगर->hash.flags & XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP)
			seq_माला_दो(m, "- IPv4 + TCP\n");
		अगर (vअगर->hash.flags & XEN_NETIF_CTRL_HASH_TYPE_IPV6)
			seq_माला_दो(m, "- IPv6\n");
		अगर (vअगर->hash.flags & XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP)
			seq_माला_दो(m, "- IPv6 + TCP\n");
	पूर्ण

	seq_माला_दो(m, "\nHash Key:\n");

	क्रम (i = 0; i < XEN_NETBK_MAX_HASH_KEY_SIZE; ) अणु
		अचिन्हित पूर्णांक j, n;

		n = 8;
		अगर (i + n >= XEN_NETBK_MAX_HASH_KEY_SIZE)
			n = XEN_NETBK_MAX_HASH_KEY_SIZE - i;

		seq_म_लिखो(m, "[%2u - %2u]: ", i, i + n - 1);

		क्रम (j = 0; j < n; j++, i++)
			seq_म_लिखो(m, "%02x ", vअगर->hash.key[i]);

		seq_माला_दो(m, "\n");
	पूर्ण

	अगर (vअगर->hash.size != 0) अणु
		स्थिर u32 *mapping = vअगर->hash.mapping[vअगर->hash.mapping_sel];

		seq_माला_दो(m, "\nHash Mapping:\n");

		क्रम (i = 0; i < vअगर->hash.size; ) अणु
			अचिन्हित पूर्णांक j, n;

			n = 8;
			अगर (i + n >= vअगर->hash.size)
				n = vअगर->hash.size - i;

			seq_म_लिखो(m, "[%4u - %4u]: ", i, i + n - 1);

			क्रम (j = 0; j < n; j++, i++)
				seq_म_लिखो(m, "%4u ", mapping[i]);

			seq_माला_दो(m, "\n");
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

व्योम xenvअगर_init_hash(काष्ठा xenvअगर *vअगर)
अणु
	अगर (xenvअगर_hash_cache_size == 0)
		वापस;

	BUG_ON(vअगर->hash.cache.count);

	spin_lock_init(&vअगर->hash.cache.lock);
	INIT_LIST_HEAD(&vअगर->hash.cache.list);
पूर्ण

व्योम xenvअगर_deinit_hash(काष्ठा xenvअगर *vअगर)
अणु
	xenvअगर_flush_hash(vअगर);
पूर्ण
