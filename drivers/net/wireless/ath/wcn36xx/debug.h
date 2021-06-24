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

#अगर_अघोषित _WCN36XX_DEBUG_H_
#घोषणा _WCN36XX_DEBUG_H_

#समावेश <linux/kernel.h>

#घोषणा WCN36xx_MAX_DUMP_ARGS	5

#अगर_घोषित CONFIG_WCN36XX_DEBUGFS
काष्ठा wcn36xx_dfs_file अणु
	काष्ठा dentry *dentry;
	u32 value;
पूर्ण;

काष्ठा wcn36xx_dfs_entry अणु
	काष्ठा dentry *rootdir;
	काष्ठा wcn36xx_dfs_file file_bmps_चयनer;
	काष्ठा wcn36xx_dfs_file file_dump;
पूर्ण;

व्योम wcn36xx_debugfs_init(काष्ठा wcn36xx *wcn);
व्योम wcn36xx_debugfs_निकास(काष्ठा wcn36xx *wcn);

#अन्यथा
अटल अंतरभूत व्योम wcn36xx_debugfs_init(काष्ठा wcn36xx *wcn)
अणु
पूर्ण
अटल अंतरभूत व्योम wcn36xx_debugfs_निकास(काष्ठा wcn36xx *wcn)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_WCN36XX_DEBUGFS */

#पूर्ण_अगर	/* _WCN36XX_DEBUG_H_ */
