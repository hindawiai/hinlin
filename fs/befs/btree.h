<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * btree.h
 *
 */

पूर्णांक befs_btree_find(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
		    स्थिर अक्षर *key, befs_off_t *value);

पूर्णांक befs_btree_पढ़ो(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
		    loff_t key_no, माप_प्रकार bufsize, अक्षर *keybuf,
		    माप_प्रकार *keysize, befs_off_t *value);
