<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __RSI_DEBUGFS_H__
#घोषणा __RSI_DEBUGFS_H__

#समावेश "rsi_main.h"
#समावेश <linux/debugfs.h>

#अगर_अघोषित CONFIG_RSI_DEBUGFS
अटल अंतरभूत पूर्णांक rsi_init_dbgfs(काष्ठा rsi_hw *adapter)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rsi_हटाओ_dbgfs(काष्ठा rsi_hw *adapter)
अणु
	वापस;
पूर्ण
#अन्यथा
काष्ठा rsi_dbg_files अणु
	स्थिर अक्षर *name;
	umode_t perms;
	स्थिर काष्ठा file_operations fops;
पूर्ण;

काष्ठा rsi_debugfs अणु
	काष्ठा dentry *subdir;
	काष्ठा rsi_dbg_ops *dfs_get_ops;
	काष्ठा dentry *rsi_files[MAX_DEBUGFS_ENTRIES];
पूर्ण;
पूर्णांक rsi_init_dbgfs(काष्ठा rsi_hw *adapter);
व्योम rsi_हटाओ_dbgfs(काष्ठा rsi_hw *adapter);
#पूर्ण_अगर
#पूर्ण_अगर
