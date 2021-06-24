<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/mpage.h
 *
 * Contains declarations related to preparing and submitting BIOS which contain
 * multiple pagecache pages.
 */

/*
 * (And no, it करोesn't do the #ifdef __MPAGE_H thing, and it doesn't करो
 * nested includes.  Get it right in the .c file).
 */
#अगर_घोषित CONFIG_BLOCK

काष्ठा ग_लिखोback_control;
काष्ठा पढ़ोahead_control;

व्योम mpage_पढ़ोahead(काष्ठा पढ़ोahead_control *, get_block_t get_block);
पूर्णांक mpage_पढ़ोpage(काष्ठा page *page, get_block_t get_block);
पूर्णांक mpage_ग_लिखोpages(काष्ठा address_space *mapping,
		काष्ठा ग_लिखोback_control *wbc, get_block_t get_block);
पूर्णांक mpage_ग_लिखोpage(काष्ठा page *page, get_block_t *get_block,
		काष्ठा ग_लिखोback_control *wbc);

#पूर्ण_अगर
