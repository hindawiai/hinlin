<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MM_PAGE_REPORTING_H
#घोषणा _MM_PAGE_REPORTING_H

#समावेश <linux/mmzone.h>
#समावेश <linux/pageblock-flags.h>
#समावेश <linux/page-isolation.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/slab.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/scatterlist.h>

#घोषणा PAGE_REPORTING_MIN_ORDER	pageblock_order

#अगर_घोषित CONFIG_PAGE_REPORTING
DECLARE_STATIC_KEY_FALSE(page_reporting_enabled);
व्योम __page_reporting_notअगरy(व्योम);

अटल अंतरभूत bool page_reported(काष्ठा page *page)
अणु
	वापस अटल_branch_unlikely(&page_reporting_enabled) &&
	       PageReported(page);
पूर्ण

/**
 * page_reporting_notअगरy_मुक्त - Free page notअगरication to start page processing
 *
 * This function is meant to act as a screener क्रम __page_reporting_notअगरy
 * which will determine अगर a give zone has crossed over the high-water mark
 * that will justअगरy us beginning page treaपंचांगent. If we have crossed that
 * threshold then it will start the process of pulling some pages and
 * placing them in the batch list क्रम treaपंचांगent.
 */
अटल अंतरभूत व्योम page_reporting_notअगरy_मुक्त(अचिन्हित पूर्णांक order)
अणु
	/* Called from hot path in __मुक्त_one_page() */
	अगर (!अटल_branch_unlikely(&page_reporting_enabled))
		वापस;

	/* Determine अगर we have crossed reporting threshold */
	अगर (order < PAGE_REPORTING_MIN_ORDER)
		वापस;

	/* This will add a few cycles, but should be called infrequently */
	__page_reporting_notअगरy();
पूर्ण
#अन्यथा /* CONFIG_PAGE_REPORTING */
#घोषणा page_reported(_page)	false

अटल अंतरभूत व्योम page_reporting_notअगरy_मुक्त(अचिन्हित पूर्णांक order)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PAGE_REPORTING */
#पूर्ण_अगर /*_MM_PAGE_REPORTING_H */
