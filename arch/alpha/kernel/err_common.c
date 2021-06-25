<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/err_common.c
 *
 *	Copyright (C) 2000 Jeff Wiedemeier (Compaq Computer Corporation)
 *
 *	Error handling code supporting Alpha प्रणालीs
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/err_common.h>

#समावेश "err_impl.h"
#समावेश "proto.h"

/*
 * err_prपूर्णांक_prefix -- error handling prपूर्णांक routines should prefix
 * all prपूर्णांकs with this
 */
अक्षर *err_prपूर्णांक_prefix = KERN_NOTICE;


/*
 * Generic
 */
व्योम
mchk_dump_mem(व्योम *data, माप_प्रकार length, अक्षर **annotation)
अणु
	अचिन्हित दीर्घ *ldata = data;
	माप_प्रकार i;
	
	क्रम (i = 0; (i * माप(*ldata)) < length; i++) अणु
		अगर (annotation && !annotation[i]) 
			annotation = शून्य;
		prपूर्णांकk("%s    %08x: %016lx    %s\n",
		       err_prपूर्णांक_prefix,
		       (अचिन्हित)(i * माप(*ldata)), ldata[i],
		       annotation ? annotation[i] : "");
	पूर्ण
पूर्ण

व्योम
mchk_dump_logout_frame(काष्ठा el_common *mchk_header)
अणु
	prपूर्णांकk("%s  -- Frame Header --\n"
	         "    Frame Size:   %d (0x%x) bytes\n"
	         "    Flags:        %s%s\n"
	         "    MCHK Code:    0x%x\n"
	         "    Frame Rev:    %d\n"
	         "    Proc Offset:  0x%08x\n"
	         "    Sys Offset:   0x%08x\n"
  	         "  -- Processor Region --\n",
	       err_prपूर्णांक_prefix, 
	       mchk_header->size, mchk_header->size,
	       mchk_header->retry ? "RETRY " : "", 
  	         mchk_header->err2 ? "SECOND_ERR " : "",
	       mchk_header->code,
	       mchk_header->frame_rev,
	       mchk_header->proc_offset,
	       mchk_header->sys_offset);

	mchk_dump_mem((व्योम *)
		      ((अचिन्हित दीर्घ)mchk_header + mchk_header->proc_offset),
		      mchk_header->sys_offset - mchk_header->proc_offset,
		      शून्य);
	
	prपूर्णांकk("%s  -- System Region --\n", err_prपूर्णांक_prefix);
	mchk_dump_mem((व्योम *)
		      ((अचिन्हित दीर्घ)mchk_header + mchk_header->sys_offset),
		      mchk_header->size - mchk_header->sys_offset,
		      शून्य);
	prपूर्णांकk("%s  -- End of Frame --\n", err_prपूर्णांक_prefix);
पूर्ण


/*
 * Console Data Log
 */
/* Data */
अटल काष्ठा el_subpacket_handler *subpacket_handler_list = शून्य;
अटल काष्ठा el_subpacket_annotation *subpacket_annotation_list = शून्य;

अटल काष्ठा el_subpacket *
el_process_header_subpacket(काष्ठा el_subpacket *header)
अणु
	जोड़ el_बारtamp बारtamp;
	अक्षर *name = "UNKNOWN EVENT";
	पूर्णांक packet_count = 0;
	पूर्णांक length = 0;

	अगर (header->class != EL_CLASS__HEADER) अणु
		prपूर्णांकk("%s** Unexpected header CLASS %d TYPE %d, aborting\n",
		       err_prपूर्णांक_prefix,
		       header->class, header->type);
		वापस शून्य;
	पूर्ण

	चयन(header->type) अणु
	हाल EL_TYPE__HEADER__SYSTEM_ERROR_FRAME:
		name = "SYSTEM ERROR";
		length = header->by_type.sys_err.frame_length;
		packet_count = 
			header->by_type.sys_err.frame_packet_count;
		बारtamp.as_पूर्णांक = 0;
		अवरोध;
	हाल EL_TYPE__HEADER__SYSTEM_EVENT_FRAME:
		name = "SYSTEM EVENT";
		length = header->by_type.sys_event.frame_length;
		packet_count = 
			header->by_type.sys_event.frame_packet_count;
		बारtamp = header->by_type.sys_event.बारtamp;
		अवरोध;
	हाल EL_TYPE__HEADER__HALT_FRAME:
		name = "ERROR HALT";
		length = header->by_type.err_halt.frame_length;
		packet_count = 
			header->by_type.err_halt.frame_packet_count;
		बारtamp = header->by_type.err_halt.बारtamp;
		अवरोध;
	हाल EL_TYPE__HEADER__LOGOUT_FRAME:
		name = "LOGOUT FRAME";
		length = header->by_type.logout_header.frame_length;
		packet_count = 1;
		बारtamp.as_पूर्णांक = 0;
		अवरोध;
	शेष: /* Unknown */
		prपूर्णांकk("%s** Unknown header - CLASS %d TYPE %d, aborting\n",
		       err_prपूर्णांक_prefix,
		       header->class, header->type);
		वापस शून्य;		
	पूर्ण

	prपूर्णांकk("%s*** %s:\n"
	         "  CLASS %d, TYPE %d\n", 
	       err_prपूर्णांक_prefix,
	       name,
	       header->class, header->type);
	el_prपूर्णांक_बारtamp(&बारtamp);
	
	/*
	 * Process the subpackets
	 */
	el_process_subpackets(header, packet_count);

	/* वापस the next header */
	header = (काष्ठा el_subpacket *)
		((अचिन्हित दीर्घ)header + header->length + length);
	वापस header;
पूर्ण

अटल काष्ठा el_subpacket *
el_process_subpacket_reg(काष्ठा el_subpacket *header)
अणु
	काष्ठा el_subpacket *next = शून्य;
	काष्ठा el_subpacket_handler *h = subpacket_handler_list;

	क्रम (; h && h->class != header->class; h = h->next);
	अगर (h) next = h->handler(header);

	वापस next;
पूर्ण

व्योम
el_prपूर्णांक_बारtamp(जोड़ el_बारtamp *बारtamp)
अणु
	अगर (बारtamp->as_पूर्णांक)
		prपूर्णांकk("%s  TIMESTAMP: %d/%d/%02d %d:%02d:%0d\n", 
		       err_prपूर्णांक_prefix,
		       बारtamp->b.month, बारtamp->b.day,
		       बारtamp->b.year, बारtamp->b.hour,
		       बारtamp->b.minute, बारtamp->b.second);
पूर्ण

व्योम
el_process_subpackets(काष्ठा el_subpacket *header, पूर्णांक packet_count)
अणु
	काष्ठा el_subpacket *subpacket;
	पूर्णांक i;

	subpacket = (काष्ठा el_subpacket *)
		((अचिन्हित दीर्घ)header + header->length);

	क्रम (i = 0; subpacket && i < packet_count; i++) अणु
		prपूर्णांकk("%sPROCESSING SUBPACKET %d\n", err_prपूर्णांक_prefix, i);
		subpacket = el_process_subpacket(subpacket);
	पूर्ण
पूर्ण

काष्ठा el_subpacket *
el_process_subpacket(काष्ठा el_subpacket *header)
अणु
	काष्ठा el_subpacket *next = शून्य;

	चयन(header->class) अणु
	हाल EL_CLASS__TERMINATION:
		/* Termination packet, there are no more */
		अवरोध;
	हाल EL_CLASS__HEADER: 
		next = el_process_header_subpacket(header);
		अवरोध;
	शेष:
		अगर (शून्य == (next = el_process_subpacket_reg(header))) अणु
			prपूर्णांकk("%s** Unexpected header CLASS %d TYPE %d"
			       " -- aborting.\n",
			       err_prपूर्णांक_prefix,
			       header->class, header->type);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस next;
पूर्ण

व्योम 
el_annotate_subpacket(काष्ठा el_subpacket *header)
अणु
	काष्ठा el_subpacket_annotation *a;
	अक्षर **annotation = शून्य;

	क्रम (a = subpacket_annotation_list; a; a = a->next) अणु
		अगर (a->class == header->class &&
		    a->type == header->type &&
		    a->revision == header->revision) अणु
			/*
			 * We found the annotation
			 */
			annotation = a->annotation;
			prपूर्णांकk("%s  %s\n", err_prपूर्णांक_prefix, a->description);
			अवरोध;
		पूर्ण
	पूर्ण

	mchk_dump_mem(header, header->length, annotation);
पूर्ण

अटल व्योम __init
cdl_process_console_data_log(पूर्णांक cpu, काष्ठा percpu_काष्ठा *pcpu)
अणु
	काष्ठा el_subpacket *header = (काष्ठा el_subpacket *)
		(IDENT_ADDR | pcpu->console_data_log_pa);
	पूर्णांक err;

	prपूर्णांकk("%s******* CONSOLE DATA LOG FOR CPU %d. *******\n"
	         "*** Error(s) were logged on a previous boot\n",
	       err_prपूर्णांक_prefix, cpu);
	
	क्रम (err = 0; header && (header->class != EL_CLASS__TERMINATION); err++)
		header = el_process_subpacket(header);

	/* let the console know it's ok to clear the error(s) at restart */
	pcpu->console_data_log_pa = 0;

	prपूर्णांकk("%s*** %d total error(s) logged\n"
	         "**** END OF CONSOLE DATA LOG FOR CPU %d ****\n", 
	       err_prपूर्णांक_prefix, err, cpu);
पूर्ण

व्योम __init
cdl_check_console_data_log(व्योम)
अणु
	काष्ठा percpu_काष्ठा *pcpu;
	अचिन्हित दीर्घ cpu;

	क्रम (cpu = 0; cpu < hwrpb->nr_processors; cpu++) अणु
		pcpu = (काष्ठा percpu_काष्ठा *)
			((अचिन्हित दीर्घ)hwrpb + hwrpb->processor_offset 
			 + cpu * hwrpb->processor_size);
		अगर (pcpu->console_data_log_pa)
			cdl_process_console_data_log(cpu, pcpu);
	पूर्ण

पूर्ण

पूर्णांक __init
cdl_रेजिस्टर_subpacket_annotation(काष्ठा el_subpacket_annotation *new)
अणु
	काष्ठा el_subpacket_annotation *a = subpacket_annotation_list;

	अगर (a == शून्य) subpacket_annotation_list = new;
	अन्यथा अणु
		क्रम (; a->next != शून्य; a = a->next) अणु
			अगर ((a->class == new->class && a->type == new->type) ||
			    a == new) अणु
				prपूर्णांकk("Attempted to re-register "
				       "subpacket annotation\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		a->next = new;
	पूर्ण
	new->next = शून्य;

	वापस 0;
पूर्ण

पूर्णांक __init
cdl_रेजिस्टर_subpacket_handler(काष्ठा el_subpacket_handler *new)
अणु
	काष्ठा el_subpacket_handler *h = subpacket_handler_list;

	अगर (h == शून्य) subpacket_handler_list = new;
	अन्यथा अणु
		क्रम (; h->next != शून्य; h = h->next) अणु
			अगर (h->class == new->class || h == new) अणु
				prपूर्णांकk("Attempted to re-register "
				       "subpacket handler\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		h->next = new;
	पूर्ण
	new->next = शून्य;

	वापस 0;
पूर्ण

