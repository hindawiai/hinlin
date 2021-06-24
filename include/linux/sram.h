<शैली गुरु>
/*
 * Generic SRAM Driver Interface
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित __LINUX_SRAM_H__
#घोषणा __LINUX_SRAM_H__

काष्ठा gen_pool;

#अगर_घोषित CONFIG_SRAM_EXEC
व्योम *sram_exec_copy(काष्ठा gen_pool *pool, व्योम *dst, व्योम *src, माप_प्रकार size);
#अन्यथा
अटल अंतरभूत व्योम *sram_exec_copy(काष्ठा gen_pool *pool, व्योम *dst, व्योम *src,
				   माप_प्रकार size)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_SRAM_EXEC */
#पूर्ण_अगर /* __LINUX_SRAM_H__ */
