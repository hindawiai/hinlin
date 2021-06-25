<शैली गुरु>
/*
 * Copyright (c) 2013 Eugene Krasnikov <k.eugene.e@gmail.com>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश "wcn36xx.h"
#समावेश "debug.h"
#समावेश "pmc.h"

#अगर_घोषित CONFIG_WCN36XX_DEBUGFS

अटल sमाप_प्रकार पढ़ो_file_bool_bmps(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wcn36xx *wcn = file->निजी_data;
	काष्ठा wcn36xx_vअगर *vअगर_priv = शून्य;
	काष्ठा ieee80211_vअगर *vअगर = शून्य;
	अक्षर buf[3];

	list_क्रम_each_entry(vअगर_priv, &wcn->vअगर_list, list) अणु
			vअगर = wcn36xx_priv_to_vअगर(vअगर_priv);
			अगर (NL80211_IFTYPE_STATION == vअगर->type) अणु
				अगर (vअगर_priv->pw_state == WCN36XX_BMPS)
					buf[0] = '1';
				अन्यथा
					buf[0] = '0';
				अवरोध;
			पूर्ण
	पूर्ण
	buf[1] = '\n';
	buf[2] = 0x00;

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_bool_bmps(काष्ठा file *file,
				    स्थिर अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wcn36xx *wcn = file->निजी_data;
	काष्ठा wcn36xx_vअगर *vअगर_priv = शून्य;
	काष्ठा ieee80211_vअगर *vअगर = शून्य;

	अक्षर buf[32];
	पूर्णांक buf_size;

	buf_size = min(count, (माप(buf)-1));
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	चयन (buf[0]) अणु
	हाल 'y':
	हाल 'Y':
	हाल '1':
		list_क्रम_each_entry(vअगर_priv, &wcn->vअगर_list, list) अणु
			vअगर = wcn36xx_priv_to_vअगर(vअगर_priv);
			अगर (NL80211_IFTYPE_STATION == vअगर->type) अणु
				wcn36xx_enable_keep_alive_null_packet(wcn, vअगर);
				wcn36xx_pmc_enter_bmps_state(wcn, vअगर);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 'n':
	हाल 'N':
	हाल '0':
		list_क्रम_each_entry(vअगर_priv, &wcn->vअगर_list, list) अणु
			vअगर = wcn36xx_priv_to_vअगर(vअगर_priv);
			अगर (NL80211_IFTYPE_STATION == vअगर->type)
				wcn36xx_pmc_निकास_bmps_state(wcn, vअगर);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_wcn36xx_bmps = अणु
	.खोलो = simple_खोलो,
	.पढ़ो  =       पढ़ो_file_bool_bmps,
	.ग_लिखो =       ग_लिखो_file_bool_bmps,
पूर्ण;

अटल sमाप_प्रकार ग_लिखो_file_dump(काष्ठा file *file,
				    स्थिर अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wcn36xx *wcn = file->निजी_data;
	अक्षर buf[255], *पंचांगp;
	पूर्णांक buf_size;
	u32 arg[WCN36xx_MAX_DUMP_ARGS];
	पूर्णांक i;

	स_रखो(buf, 0, माप(buf));
	स_रखो(arg, 0, माप(arg));

	buf_size = min(count, (माप(buf) - 1));
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	पंचांगp = buf;

	क्रम (i = 0; i < WCN36xx_MAX_DUMP_ARGS; i++) अणु
		अक्षर *begin;
		begin = strsep(&पंचांगp, " ");
		अगर (begin == शून्य)
			अवरोध;

		अगर (kstrtou32(begin, 0, &arg[i]) != 0)
			अवरोध;
	पूर्ण

	wcn36xx_info("DUMP args is %d %d %d %d %d\n", arg[0], arg[1], arg[2],
		     arg[3], arg[4]);
	wcn36xx_smd_dump_cmd_req(wcn, arg[0], arg[1], arg[2], arg[3], arg[4]);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_wcn36xx_dump = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो =       ग_लिखो_file_dump,
पूर्ण;

#घोषणा ADD_खाता(name, mode, fop, priv_data)		\
	करो अणु							\
		काष्ठा dentry *d;				\
		d = debugfs_create_file(__stringअगरy(name),	\
					mode, dfs->rootdir,	\
					priv_data, fop);	\
		dfs->file_##name.dentry = d;			\
		अगर (IS_ERR(d)) अणु				\
			wcn36xx_warn("Create the debugfs entry failed");\
			dfs->file_##name.dentry = शून्य;		\
		पूर्ण						\
	पूर्ण जबतक (0)


व्योम wcn36xx_debugfs_init(काष्ठा wcn36xx *wcn)
अणु
	काष्ठा wcn36xx_dfs_entry *dfs = &wcn->dfs;

	dfs->rootdir = debugfs_create_dir(KBUILD_MODNAME,
					  wcn->hw->wiphy->debugfsdir);
	अगर (IS_ERR(dfs->rootdir)) अणु
		wcn36xx_warn("Create the debugfs failed\n");
		dfs->rootdir = शून्य;
	पूर्ण

	ADD_खाता(bmps_चयनer, 0600, &fops_wcn36xx_bmps, wcn);
	ADD_खाता(dump, 0200, &fops_wcn36xx_dump, wcn);
पूर्ण

व्योम wcn36xx_debugfs_निकास(काष्ठा wcn36xx *wcn)
अणु
	काष्ठा wcn36xx_dfs_entry *dfs = &wcn->dfs;
	debugfs_हटाओ_recursive(dfs->rootdir);
पूर्ण

#पूर्ण_अगर /* CONFIG_WCN36XX_DEBUGFS */
