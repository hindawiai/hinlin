<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __DEBUGFS_H__
#घोषणा __DEBUGFS_H__

#समावेश "wlcore.h"

__म_लिखो(4, 5) पूर्णांक wl1271_क्रमmat_buffer(अक्षर __user *userbuf, माप_प्रकार count,
					loff_t *ppos, अक्षर *fmt, ...);

पूर्णांक wl1271_debugfs_init(काष्ठा wl1271 *wl);
व्योम wl1271_debugfs_निकास(काष्ठा wl1271 *wl);
व्योम wl1271_debugfs_reset(काष्ठा wl1271 *wl);
व्योम wl1271_debugfs_update_stats(काष्ठा wl1271 *wl);

#घोषणा DEBUGFS_FORMAT_BUFFER_SIZE 256

#घोषणा DEBUGFS_READONLY_खाता(name, fmt, value...)			\
अटल sमाप_प्रकार name## _पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,	\
			    माप_प्रकार count, loff_t *ppos)			\
अणु									\
	काष्ठा wl1271 *wl = file->निजी_data;				\
	वापस wl1271_क्रमmat_buffer(userbuf, count, ppos,		\
				    fmt "\n", ##value);			\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations name## _ops = अणु			\
	.पढ़ो = name## _पढ़ो,						\
	.खोलो = simple_खोलो,						\
	.llseek	= generic_file_llseek,					\
पूर्ण;

#घोषणा DEBUGFS_ADD(name, parent)					\
	करो अणु								\
		debugfs_create_file(#name, 0400, parent,		\
				    wl, &name## _ops);			\
	पूर्ण जबतक (0)


#घोषणा DEBUGFS_ADD_PREFIX(prefix, name, parent)			\
	करो अणु								\
		debugfs_create_file(#name, 0400, parent,		\
				    wl, &prefix## _## name## _ops);	\
	पूर्ण जबतक (0)

#घोषणा DEBUGFS_FWSTATS_खाता(sub, name, fmt, काष्ठा_type)		\
अटल sमाप_प्रकार sub## _ ##name## _पढ़ो(काष्ठा file *file,		\
				      अक्षर __user *userbuf,		\
				      माप_प्रकार count, loff_t *ppos)	\
अणु									\
	काष्ठा wl1271 *wl = file->निजी_data;				\
	काष्ठा काष्ठा_type *stats = wl->stats.fw_stats;			\
									\
	wl1271_debugfs_update_stats(wl);				\
									\
	वापस wl1271_क्रमmat_buffer(userbuf, count, ppos, fmt "\n",	\
				    stats->sub.name);			\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations sub## _ ##name## _ops = अणु		\
	.पढ़ो = sub## _ ##name## _पढ़ो,					\
	.खोलो = simple_खोलो,						\
	.llseek	= generic_file_llseek,					\
पूर्ण;

#घोषणा DEBUGFS_FWSTATS_खाता_ARRAY(sub, name, len, काष्ठा_type)		\
अटल sमाप_प्रकार sub## _ ##name## _पढ़ो(काष्ठा file *file,		\
				      अक्षर __user *userbuf,		\
				      माप_प्रकार count, loff_t *ppos)	\
अणु									\
	काष्ठा wl1271 *wl = file->निजी_data;				\
	काष्ठा काष्ठा_type *stats = wl->stats.fw_stats;			\
	अक्षर buf[DEBUGFS_FORMAT_BUFFER_SIZE] = "";			\
	पूर्णांक pos = 0;							\
	पूर्णांक i;								\
									\
	wl1271_debugfs_update_stats(wl);				\
									\
	क्रम (i = 0; i < len && pos < माप(buf); i++)			\
		pos += snम_लिखो(buf + pos, माप(buf) - pos,		\
			 "[%d] = %d\n", i, stats->sub.name[i]);		\
									\
	वापस wl1271_क्रमmat_buffer(userbuf, count, ppos, "%s", buf);	\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations sub## _ ##name## _ops = अणु		\
	.पढ़ो = sub## _ ##name## _पढ़ो,					\
	.खोलो = simple_खोलो,						\
	.llseek	= generic_file_llseek,					\
पूर्ण;

#घोषणा DEBUGFS_FWSTATS_ADD(sub, name)					\
	DEBUGFS_ADD(sub## _ ##name, stats)


#पूर्ण_अगर /* WL1271_DEBUGFS_H */
