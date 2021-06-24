<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित UBI_WL_H
#घोषणा UBI_WL_H
#अगर_घोषित CONFIG_MTD_UBI_FASTMAP
अटल व्योम update_fasपंचांगap_work_fn(काष्ठा work_काष्ठा *wrk);
अटल काष्ठा ubi_wl_entry *find_anchor_wl_entry(काष्ठा rb_root *root);
अटल काष्ठा ubi_wl_entry *get_peb_क्रम_wl(काष्ठा ubi_device *ubi);
अटल व्योम ubi_fasपंचांगap_बंद(काष्ठा ubi_device *ubi);
अटल अंतरभूत व्योम ubi_fasपंचांगap_init(काष्ठा ubi_device *ubi, पूर्णांक *count)
अणु
	/* Reserve enough LEBs to store two fasपंचांगaps. */
	*count += (ubi->fm_size / ubi->leb_size) * 2;
	INIT_WORK(&ubi->fm_work, update_fasपंचांगap_work_fn);
पूर्ण
अटल काष्ठा ubi_wl_entry *may_reserve_क्रम_fm(काष्ठा ubi_device *ubi,
					       काष्ठा ubi_wl_entry *e,
					       काष्ठा rb_root *root);
#अन्यथा /* !CONFIG_MTD_UBI_FASTMAP */
अटल काष्ठा ubi_wl_entry *get_peb_क्रम_wl(काष्ठा ubi_device *ubi);
अटल अंतरभूत व्योम ubi_fasपंचांगap_बंद(काष्ठा ubi_device *ubi) अणु पूर्ण
अटल अंतरभूत व्योम ubi_fasपंचांगap_init(काष्ठा ubi_device *ubi, पूर्णांक *count) अणु पूर्ण
अटल काष्ठा ubi_wl_entry *may_reserve_क्रम_fm(काष्ठा ubi_device *ubi,
					       काष्ठा ubi_wl_entry *e,
					       काष्ठा rb_root *root) अणु
	वापस e;
पूर्ण
#पूर्ण_अगर /* CONFIG_MTD_UBI_FASTMAP */
#पूर्ण_अगर /* UBI_WL_H */
