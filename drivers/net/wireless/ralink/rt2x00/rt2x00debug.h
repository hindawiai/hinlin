<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00debug
	Abstract: Data काष्ठाures क्रम the rt2x00debug.
 */

#अगर_अघोषित RT2X00DEBUG_H
#घोषणा RT2X00DEBUG_H

काष्ठा rt2x00_dev;

/**
 * क्रमागत rt2x00debugfs_entry_flags: Flags क्रम debugfs registry entry
 *
 * @RT2X00DEBUGFS_OFFSET: rt2x00lib should pass the रेजिस्टर offset
 *	as argument when using the callback function पढ़ो()/ग_लिखो()
 */
क्रमागत rt2x00debugfs_entry_flags अणु
	RT2X00DEBUGFS_OFFSET	= (1 << 0),
पूर्ण;

#घोषणा RT2X00DEBUGFS_REGISTER_ENTRY(__name, __type)		\
काष्ठा reg##__name अणु						\
	__type (*पढ़ो)(काष्ठा rt2x00_dev *rt2x00dev,		\
		     स्थिर अचिन्हित पूर्णांक word);			\
	व्योम (*ग_लिखो)(काष्ठा rt2x00_dev *rt2x00dev,		\
		      स्थिर अचिन्हित पूर्णांक word, __type data);	\
								\
	अचिन्हित पूर्णांक flags;					\
								\
	अचिन्हित पूर्णांक word_base;					\
	अचिन्हित पूर्णांक word_size;					\
	अचिन्हित पूर्णांक word_count;				\
पूर्ण __name

काष्ठा rt2x00debug अणु
	/*
	 * Reference to the modules काष्ठाure.
	 */
	काष्ठा module *owner;

	/*
	 * Register access entries.
	 */
	RT2X00DEBUGFS_REGISTER_ENTRY(csr, u32);
	RT2X00DEBUGFS_REGISTER_ENTRY(eeprom, u16);
	RT2X00DEBUGFS_REGISTER_ENTRY(bbp, u8);
	RT2X00DEBUGFS_REGISTER_ENTRY(rf, u32);
	RT2X00DEBUGFS_REGISTER_ENTRY(rfcsr, u8);
पूर्ण;

#पूर्ण_अगर /* RT2X00DEBUG_H */
