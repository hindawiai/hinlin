<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * hvcserver.c
 * Copyright (C) 2004 Ryan S Arnold, IBM Corporation
 *
 * PPC64 भव I/O console server support.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/hvcserver.h>
#समावेश <यंत्र/पन.स>

#घोषणा HVCS_ARCH_VERSION "1.0.0"

MODULE_AUTHOR("Ryan S. Arnold <rsa@us.ibm.com>");
MODULE_DESCRIPTION("IBM hvcs ppc64 API");
MODULE_LICENSE("GPL");
MODULE_VERSION(HVCS_ARCH_VERSION);

/*
 * Convert arch specअगरic वापस codes पूर्णांकo relevant त्रुटि_संs.  The hvcs
 * functions aren't performance sensitive, so this conversion isn't an
 * issue.
 */
अटल पूर्णांक hvcs_convert(दीर्घ to_convert)
अणु
	चयन (to_convert) अणु
		हाल H_SUCCESS:
			वापस 0;
		हाल H_PARAMETER:
			वापस -EINVAL;
		हाल H_HARDWARE:
			वापस -EIO;
		हाल H_BUSY:
		हाल H_LONG_BUSY_ORDER_1_MSEC:
		हाल H_LONG_BUSY_ORDER_10_MSEC:
		हाल H_LONG_BUSY_ORDER_100_MSEC:
		हाल H_LONG_BUSY_ORDER_1_SEC:
		हाल H_LONG_BUSY_ORDER_10_SEC:
		हाल H_LONG_BUSY_ORDER_100_SEC:
			वापस -EBUSY;
		हाल H_FUNCTION:
		शेष:
			वापस -EPERM;
	पूर्ण
पूर्ण

/**
 * hvcs_मुक्त_partner_info - मुक्त pi allocated by hvcs_get_partner_info
 * @head: list_head poपूर्णांकer क्रम an allocated list of partner info काष्ठाs to
 *	मुक्त.
 *
 * This function is used to मुक्त the partner info list that was वापसed by
 * calling hvcs_get_partner_info().
 */
पूर्णांक hvcs_मुक्त_partner_info(काष्ठा list_head *head)
अणु
	काष्ठा hvcs_partner_info *pi;
	काष्ठा list_head *element;

	अगर (!head)
		वापस -EINVAL;

	जबतक (!list_empty(head)) अणु
		element = head->next;
		pi = list_entry(element, काष्ठा hvcs_partner_info, node);
		list_del(element);
		kमुक्त(pi);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hvcs_मुक्त_partner_info);

/* Helper function क्रम hvcs_get_partner_info */
अटल पूर्णांक hvcs_next_partner(uपूर्णांक32_t unit_address,
		अचिन्हित दीर्घ last_p_partition_ID,
		अचिन्हित दीर्घ last_p_unit_address, अचिन्हित दीर्घ *pi_buff)

अणु
	दीर्घ retval;
	retval = plpar_hcall_norets(H_VTERM_PARTNER_INFO, unit_address,
			last_p_partition_ID,
				last_p_unit_address, virt_to_phys(pi_buff));
	वापस hvcs_convert(retval);
पूर्ण

/**
 * hvcs_get_partner_info - Get all of the partner info क्रम a vty-server adapter
 * @unit_address: The unit_address of the vty-server adapter क्रम which this
 *	function is fetching partner info.
 * @head: An initialized list_head poपूर्णांकer to an empty list to use to वापस the
 *	list of partner info fetched from the hypervisor to the caller.
 * @pi_buff: A page sized buffer pre-allocated prior to calling this function
 *	that is to be used to be used by firmware as an iterator to keep track
 *	of the partner info retrieval.
 *
 * This function वापसs non-zero on success, or अगर there is no partner info.
 *
 * The pi_buff is pre-allocated prior to calling this function because this
 * function may be called with a spin_lock held and kदो_स्मृति of a page is not
 * recommended as GFP_ATOMIC.
 *
 * The first दीर्घ of this buffer is used to store a partner unit address.  The
 * second दीर्घ is used to store a partner partition ID and starting at
 * pi_buff[2] is the 79 अक्षरacter Converged Location Code (dअगरf size than the
 * अचिन्हित दीर्घs, hence the casting mumbo jumbo you see later).
 *
 * Invocation of this function should always be followed by an invocation of
 * hvcs_मुक्त_partner_info() using a poपूर्णांकer to the SAME list head instance
 * that was passed as a parameter to this function.
 */
पूर्णांक hvcs_get_partner_info(uपूर्णांक32_t unit_address, काष्ठा list_head *head,
		अचिन्हित दीर्घ *pi_buff)
अणु
	/*
	 * Dealt with as दीर्घs because of the hcall पूर्णांकerface even though the
	 * values are uपूर्णांक32_t.
	 */
	अचिन्हित दीर्घ	last_p_partition_ID;
	अचिन्हित दीर्घ	last_p_unit_address;
	काष्ठा hvcs_partner_info *next_partner_info = शून्य;
	पूर्णांक more = 1;
	पूर्णांक retval;

	/* invalid parameters */
	अगर (!head || !pi_buff)
		वापस -EINVAL;

	स_रखो(pi_buff, 0x00, PAGE_SIZE);
	last_p_partition_ID = last_p_unit_address = ~0UL;
	INIT_LIST_HEAD(head);

	करो अणु
		retval = hvcs_next_partner(unit_address, last_p_partition_ID,
				last_p_unit_address, pi_buff);
		अगर (retval) अणु
			/*
			 * Don't indicate that we've failed अगर we have
			 * any list elements.
			 */
			अगर (!list_empty(head))
				वापस 0;
			वापस retval;
		पूर्ण

		last_p_partition_ID = be64_to_cpu(pi_buff[0]);
		last_p_unit_address = be64_to_cpu(pi_buff[1]);

		/* This indicates that there are no further partners */
		अगर (last_p_partition_ID == ~0UL
				&& last_p_unit_address == ~0UL)
			अवरोध;

		/* This is a very small काष्ठा and will be मुक्तd soon in
		 * hvcs_मुक्त_partner_info(). */
		next_partner_info = kदो_स्मृति(माप(काष्ठा hvcs_partner_info),
				GFP_ATOMIC);

		अगर (!next_partner_info) अणु
			prपूर्णांकk(KERN_WARNING "HVCONSOLE: kmalloc() failed to"
				" allocate partner info struct.\n");
			hvcs_मुक्त_partner_info(head);
			वापस -ENOMEM;
		पूर्ण

		next_partner_info->unit_address
			= (अचिन्हित पूर्णांक)last_p_unit_address;
		next_partner_info->partition_ID
			= (अचिन्हित पूर्णांक)last_p_partition_ID;

		/* copy the Null-term अक्षर too */
		strlcpy(&next_partner_info->location_code[0],
			(अक्षर *)&pi_buff[2],
			माप(next_partner_info->location_code));

		list_add_tail(&(next_partner_info->node), head);
		next_partner_info = शून्य;

	पूर्ण जबतक (more);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hvcs_get_partner_info);

/**
 * hvcs_रेजिस्टर_connection - establish a connection between this vty-server and
 *	a vty.
 * @unit_address: The unit address of the vty-server adapter that is to be
 *	establish a connection.
 * @p_partition_ID: The partition ID of the vty adapter that is to be connected.
 * @p_unit_address: The unit address of the vty adapter to which the vty-server
 *	is to be connected.
 *
 * If this function is called once and -EINVAL is वापसed it may
 * indicate that the partner info needs to be refreshed क्रम the
 * target unit address at which poपूर्णांक the caller must invoke
 * hvcs_get_partner_info() and then call this function again.  If,
 * क्रम a second समय, -EINVAL is वापसed then it indicates that
 * there is probably alपढ़ोy a partner connection रेजिस्टरed to a
 * dअगरferent vty-server adapter.  It is also possible that a second
 * -EINVAL may indicate that one of the parms is not valid, क्रम
 * instance अगर the link was हटाओd between the vty-server adapter
 * and the vty adapter that you are trying to खोलो.  Don't shoot the
 * messenger.  Firmware implemented it this way.
 */
पूर्णांक hvcs_रेजिस्टर_connection( uपूर्णांक32_t unit_address,
		uपूर्णांक32_t p_partition_ID, uपूर्णांक32_t p_unit_address)
अणु
	दीर्घ retval;
	retval = plpar_hcall_norets(H_REGISTER_VTERM, unit_address,
				p_partition_ID, p_unit_address);
	वापस hvcs_convert(retval);
पूर्ण
EXPORT_SYMBOL(hvcs_रेजिस्टर_connection);

/**
 * hvcs_मुक्त_connection - मुक्त the connection between a vty-server and vty
 * @unit_address: The unit address of the vty-server that is to have its
 *	connection severed.
 *
 * This function is used to मुक्त the partner connection between a vty-server
 * adapter and a vty adapter.
 *
 * If -EBUSY is वापसed जारी to call this function until 0 is वापसed.
 */
पूर्णांक hvcs_मुक्त_connection(uपूर्णांक32_t unit_address)
अणु
	दीर्घ retval;
	retval = plpar_hcall_norets(H_FREE_VTERM, unit_address);
	वापस hvcs_convert(retval);
पूर्ण
EXPORT_SYMBOL(hvcs_मुक्त_connection);
