<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is क्रम all the tests relating directly to Control Flow Integrity.
 */
#समावेश "lkdtm.h"

अटल पूर्णांक called_count;

/* Function taking one argument, without a वापस value. */
अटल noअंतरभूत व्योम lkdपंचांग_increment_व्योम(पूर्णांक *counter)
अणु
	(*counter)++;
पूर्ण

/* Function taking one argument, वापसing पूर्णांक. */
अटल noअंतरभूत पूर्णांक lkdपंचांग_increment_पूर्णांक(पूर्णांक *counter)
अणु
	(*counter)++;

	वापस *counter;
पूर्ण
/*
 * This tries to call an indirect function with a mismatched prototype.
 */
व्योम lkdपंचांग_CFI_FORWARD_PROTO(व्योम)
अणु
	/*
	 * Matches lkdपंचांग_increment_व्योम()'s prototype, but not
	 * lkdपंचांग_increment_पूर्णांक()'s prototype.
	 */
	व्योम (*func)(पूर्णांक *);

	pr_info("Calling matched prototype ...\n");
	func = lkdपंचांग_increment_व्योम;
	func(&called_count);

	pr_info("Calling mismatched prototype ...\n");
	func = (व्योम *)lkdपंचांग_increment_पूर्णांक;
	func(&called_count);

	pr_info("Fail: survived mismatched prototype function call!\n");
पूर्ण
