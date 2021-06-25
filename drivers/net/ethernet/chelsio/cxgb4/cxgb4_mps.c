<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Chelsio Communications, Inc. All rights reserved. */

#समावेश "cxgb4.h"

अटल पूर्णांक cxgb4_mps_ref_dec_by_mac(काष्ठा adapter *adap,
				    स्थिर u8 *addr, स्थिर u8 *mask)
अणु
	u8 biपंचांगask[] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;
	काष्ठा mps_entries_ref *mps_entry, *पंचांगp;
	पूर्णांक ret = -EINVAL;

	spin_lock_bh(&adap->mps_ref_lock);
	list_क्रम_each_entry_safe(mps_entry, पंचांगp, &adap->mps_ref, list) अणु
		अगर (ether_addr_equal(mps_entry->addr, addr) &&
		    ether_addr_equal(mps_entry->mask, mask ? mask : biपंचांगask)) अणु
			अगर (!refcount_dec_and_test(&mps_entry->refcnt)) अणु
				spin_unlock_bh(&adap->mps_ref_lock);
				वापस -EBUSY;
			पूर्ण
			list_del(&mps_entry->list);
			kमुक्त(mps_entry);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&adap->mps_ref_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक cxgb4_mps_ref_dec(काष्ठा adapter *adap, u16 idx)
अणु
	काष्ठा mps_entries_ref *mps_entry, *पंचांगp;
	पूर्णांक ret = -EINVAL;

	spin_lock(&adap->mps_ref_lock);
	list_क्रम_each_entry_safe(mps_entry, पंचांगp, &adap->mps_ref, list) अणु
		अगर (mps_entry->idx == idx) अणु
			अगर (!refcount_dec_and_test(&mps_entry->refcnt)) अणु
				spin_unlock(&adap->mps_ref_lock);
				वापस -EBUSY;
			पूर्ण
			list_del(&mps_entry->list);
			kमुक्त(mps_entry);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&adap->mps_ref_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक cxgb4_mps_ref_inc(काष्ठा adapter *adap, स्थिर u8 *mac_addr,
			     u16 idx, स्थिर u8 *mask)
अणु
	u8 biपंचांगask[] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;
	काष्ठा mps_entries_ref *mps_entry;
	पूर्णांक ret = 0;

	spin_lock_bh(&adap->mps_ref_lock);
	list_क्रम_each_entry(mps_entry, &adap->mps_ref, list) अणु
		अगर (mps_entry->idx == idx) अणु
			refcount_inc(&mps_entry->refcnt);
			जाओ unlock;
		पूर्ण
	पूर्ण
	mps_entry = kzalloc(माप(*mps_entry), GFP_ATOMIC);
	अगर (!mps_entry) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण
	ether_addr_copy(mps_entry->mask, mask ? mask : biपंचांगask);
	ether_addr_copy(mps_entry->addr, mac_addr);
	mps_entry->idx = idx;
	refcount_set(&mps_entry->refcnt, 1);
	list_add_tail(&mps_entry->list, &adap->mps_ref);
unlock:
	spin_unlock_bh(&adap->mps_ref_lock);
	वापस ret;
पूर्ण

पूर्णांक cxgb4_मुक्त_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			अचिन्हित पूर्णांक naddr, स्थिर u8 **addr, bool sleep_ok)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < naddr; i++) अणु
		अगर (!cxgb4_mps_ref_dec_by_mac(adap, addr[i], शून्य)) अणु
			ret = t4_मुक्त_mac_filt(adap, adap->mbox, viid,
					       1, &addr[i], sleep_ok);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	/* वापस number of filters मुक्तd */
	वापस naddr;
पूर्ण

पूर्णांक cxgb4_alloc_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			 bool मुक्त, अचिन्हित पूर्णांक naddr, स्थिर u8 **addr,
			 u16 *idx, u64 *hash, bool sleep_ok)
अणु
	पूर्णांक ret, i;

	ret = t4_alloc_mac_filt(adap, adap->mbox, viid, मुक्त,
				naddr, addr, idx, hash, sleep_ok);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < naddr; i++) अणु
		अगर (idx[i] != 0xffff) अणु
			अगर (cxgb4_mps_ref_inc(adap, addr[i], idx[i], शून्य)) अणु
				ret = -ENOMEM;
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

	जाओ out;
error:
	cxgb4_मुक्त_mac_filt(adap, viid, naddr, addr, sleep_ok);

out:
	/* Returns a negative error number or the number of filters allocated */
	वापस ret;
पूर्ण

पूर्णांक cxgb4_update_mac_filt(काष्ठा port_info *pi, अचिन्हित पूर्णांक viid,
			  पूर्णांक *tcam_idx, स्थिर u8 *addr,
			  bool persistent, u8 *smt_idx)
अणु
	पूर्णांक ret;

	ret = cxgb4_change_mac(pi, viid, tcam_idx,
			       addr, persistent, smt_idx);
	अगर (ret < 0)
		वापस ret;

	cxgb4_mps_ref_inc(pi->adapter, addr, *tcam_idx, शून्य);
	वापस ret;
पूर्ण

पूर्णांक cxgb4_मुक्त_raw_mac_filt(काष्ठा adapter *adap,
			    अचिन्हित पूर्णांक viid,
			    स्थिर u8 *addr,
			    स्थिर u8 *mask,
			    अचिन्हित पूर्णांक idx,
			    u8 lookup_type,
			    u8 port_id,
			    bool sleep_ok)
अणु
	पूर्णांक ret = 0;

	अगर (!cxgb4_mps_ref_dec(adap, idx))
		ret = t4_मुक्त_raw_mac_filt(adap, viid, addr,
					   mask, idx, lookup_type,
					   port_id, sleep_ok);

	वापस ret;
पूर्ण

पूर्णांक cxgb4_alloc_raw_mac_filt(काष्ठा adapter *adap,
			     अचिन्हित पूर्णांक viid,
			     स्थिर u8 *addr,
			     स्थिर u8 *mask,
			     अचिन्हित पूर्णांक idx,
			     u8 lookup_type,
			     u8 port_id,
			     bool sleep_ok)
अणु
	पूर्णांक ret;

	ret = t4_alloc_raw_mac_filt(adap, viid, addr,
				    mask, idx, lookup_type,
				    port_id, sleep_ok);
	अगर (ret < 0)
		वापस ret;

	अगर (cxgb4_mps_ref_inc(adap, addr, ret, mask)) अणु
		ret = -ENOMEM;
		t4_मुक्त_raw_mac_filt(adap, viid, addr,
				     mask, idx, lookup_type,
				     port_id, sleep_ok);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक cxgb4_मुक्त_encap_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			      पूर्णांक idx, bool sleep_ok)
अणु
	पूर्णांक ret = 0;

	अगर (!cxgb4_mps_ref_dec(adap, idx))
		ret = t4_मुक्त_encap_mac_filt(adap, viid, idx, sleep_ok);

	वापस ret;
पूर्ण

पूर्णांक cxgb4_alloc_encap_mac_filt(काष्ठा adapter *adap, अचिन्हित पूर्णांक viid,
			       स्थिर u8 *addr, स्थिर u8 *mask,
			       अचिन्हित पूर्णांक vni, अचिन्हित पूर्णांक vni_mask,
			       u8 dip_hit, u8 lookup_type, bool sleep_ok)
अणु
	पूर्णांक ret;

	ret = t4_alloc_encap_mac_filt(adap, viid, addr, mask, vni, vni_mask,
				      dip_hit, lookup_type, sleep_ok);
	अगर (ret < 0)
		वापस ret;

	अगर (cxgb4_mps_ref_inc(adap, addr, ret, mask)) अणु
		ret = -ENOMEM;
		t4_मुक्त_encap_mac_filt(adap, viid, ret, sleep_ok);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक cxgb4_init_mps_ref_entries(काष्ठा adapter *adap)
अणु
	spin_lock_init(&adap->mps_ref_lock);
	INIT_LIST_HEAD(&adap->mps_ref);

	वापस 0;
पूर्ण

व्योम cxgb4_मुक्त_mps_ref_entries(काष्ठा adapter *adap)
अणु
	काष्ठा mps_entries_ref *mps_entry, *पंचांगp;

	अगर (list_empty(&adap->mps_ref))
		वापस;

	spin_lock(&adap->mps_ref_lock);
	list_क्रम_each_entry_safe(mps_entry, पंचांगp, &adap->mps_ref, list) अणु
		list_del(&mps_entry->list);
		kमुक्त(mps_entry);
	पूर्ण
	spin_unlock(&adap->mps_ref_lock);
पूर्ण
