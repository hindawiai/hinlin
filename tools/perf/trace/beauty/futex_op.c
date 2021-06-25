<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#समावेश <linux/futex.h>

#अगर_अघोषित FUTEX_WAIT_BITSET
#घोषणा FUTEX_WAIT_BITSET	  9
#पूर्ण_अगर
#अगर_अघोषित FUTEX_WAKE_BITSET
#घोषणा FUTEX_WAKE_BITSET	 10
#पूर्ण_अगर
#अगर_अघोषित FUTEX_WAIT_REQUEUE_PI
#घोषणा FUTEX_WAIT_REQUEUE_PI	 11
#पूर्ण_अगर
#अगर_अघोषित FUTEX_CMP_REQUEUE_PI
#घोषणा FUTEX_CMP_REQUEUE_PI	 12
#पूर्ण_अगर
#अगर_अघोषित FUTEX_CLOCK_REALTIME
#घोषणा FUTEX_CLOCK_REALTIME	256
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_futex_op(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "FUTEX_";
	क्रमागत syscall_futex_args अणु
		SCF_UADDR   = (1 << 0),
		SCF_OP	    = (1 << 1),
		SCF_VAL	    = (1 << 2),
		SCF_TIMEOUT = (1 << 3),
		SCF_UADDR2  = (1 << 4),
		SCF_VAL3    = (1 << 5),
	पूर्ण;
	पूर्णांक op = arg->val;
	पूर्णांक cmd = op & FUTEX_CMD_MASK;
	माप_प्रकार prपूर्णांकed = 0;

	चयन (cmd) अणु
#घोषणा	P_FUTEX_OP(n) हाल FUTEX_##n: prपूर्णांकed = scnम_लिखो(bf, size, "%s%s", show_prefix ? prefix : "", #n);
	P_FUTEX_OP(WAIT);	    arg->mask |= SCF_VAL3|SCF_UADDR2;		  अवरोध;
	P_FUTEX_OP(WAKE);	    arg->mask |= SCF_VAL3|SCF_UADDR2|SCF_TIMEOUT; अवरोध;
	P_FUTEX_OP(FD);		    arg->mask |= SCF_VAL3|SCF_UADDR2|SCF_TIMEOUT; अवरोध;
	P_FUTEX_OP(REQUEUE);	    arg->mask |= SCF_VAL3|SCF_TIMEOUT;	          अवरोध;
	P_FUTEX_OP(CMP_REQUEUE);    arg->mask |= SCF_TIMEOUT;			  अवरोध;
	P_FUTEX_OP(CMP_REQUEUE_PI); arg->mask |= SCF_TIMEOUT;			  अवरोध;
	P_FUTEX_OP(WAKE_OP);							  अवरोध;
	P_FUTEX_OP(LOCK_PI);	    arg->mask |= SCF_VAL3|SCF_UADDR2|SCF_TIMEOUT; अवरोध;
	P_FUTEX_OP(UNLOCK_PI);	    arg->mask |= SCF_VAL3|SCF_UADDR2|SCF_TIMEOUT; अवरोध;
	P_FUTEX_OP(TRYLOCK_PI);	    arg->mask |= SCF_VAL3|SCF_UADDR2;		  अवरोध;
	P_FUTEX_OP(WAIT_BITSET);    arg->mask |= SCF_UADDR2;			  अवरोध;
	P_FUTEX_OP(WAKE_BITSET);    arg->mask |= SCF_UADDR2;			  अवरोध;
	P_FUTEX_OP(WAIT_REQUEUE_PI);						  अवरोध;
	शेष: prपूर्णांकed = scnम_लिखो(bf, size, "%#x", cmd);			  अवरोध;
	पूर्ण

	अगर (op & FUTEX_PRIVATE_FLAG)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "|%s%s", show_prefix ? prefix : "", "PRIVATE_FLAG");

	अगर (op & FUTEX_CLOCK_REALTIME)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "|%s%s", show_prefix ? prefix : "", "CLOCK_REALTIME");

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_FUTEX_OP  syscall_arg__scnम_लिखो_futex_op
