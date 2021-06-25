<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * A generic kernel FIFO implementation
 *
 * Copyright (C) 2013 Stefani Seibold <stefani@seibold.net>
 */

#अगर_अघोषित _LINUX_KFIFO_H
#घोषणा _LINUX_KFIFO_H

/*
 * How to porting drivers to the new generic FIFO API:
 *
 * - Modअगरy the declaration of the "struct kfifo *" object पूर्णांकo a
 *   in-place "struct kfifo" object
 * - Init the in-place object with kfअगरo_alloc() or kfअगरo_init()
 *   Note: The address of the in-place "struct kfifo" object must be
 *   passed as the first argument to this functions
 * - Replace the use of __kfअगरo_put पूर्णांकo kfअगरo_in and __kfअगरo_get
 *   पूर्णांकo kfअगरo_out
 * - Replace the use of kfअगरo_put पूर्णांकo kfअगरo_in_spinlocked and kfअगरo_get
 *   पूर्णांकo kfअगरo_out_spinlocked
 *   Note: the spinlock poपूर्णांकer क्रमmerly passed to kfअगरo_init/kfअगरo_alloc
 *   must be passed now to the kfअगरo_in_spinlocked and kfअगरo_out_spinlocked
 *   as the last parameter
 * - The क्रमmerly __kfअगरo_* functions are नामd पूर्णांकo kfअगरo_*
 */

/*
 * Note about locking: There is no locking required until only one पढ़ोer
 * and one ग_लिखोr is using the fअगरo and no kfअगरo_reset() will be called.
 * kfअगरo_reset_out() can be safely used, until it will be only called
 * in the पढ़ोer thपढ़ो.
 * For multiple ग_लिखोr and one पढ़ोer there is only a need to lock the ग_लिखोr.
 * And vice versa क्रम only one ग_लिखोr and multiple पढ़ोer there is only a need
 * to lock the पढ़ोer.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/scatterlist.h>

काष्ठा __kfअगरo अणु
	अचिन्हित पूर्णांक	in;
	अचिन्हित पूर्णांक	out;
	अचिन्हित पूर्णांक	mask;
	अचिन्हित पूर्णांक	esize;
	व्योम		*data;
पूर्ण;

#घोषणा __STRUCT_KFIFO_COMMON(datatype, recsize, ptrtype) \
	जोड़ अणु \
		काष्ठा __kfअगरo	kfअगरo; \
		datatype	*type; \
		स्थिर datatype	*स्थिर_type; \
		अक्षर		(*rectype)[recsize]; \
		ptrtype		*ptr; \
		ptrtype स्थिर	*ptr_स्थिर; \
	पूर्ण

#घोषणा __STRUCT_KFIFO(type, size, recsize, ptrtype) \
अणु \
	__STRUCT_KFIFO_COMMON(type, recsize, ptrtype); \
	type		buf[((size < 2) || (size & (size - 1))) ? -1 : size]; \
पूर्ण

#घोषणा STRUCT_KFIFO(type, size) \
	काष्ठा __STRUCT_KFIFO(type, size, 0, type)

#घोषणा __STRUCT_KFIFO_PTR(type, recsize, ptrtype) \
अणु \
	__STRUCT_KFIFO_COMMON(type, recsize, ptrtype); \
	type		buf[0]; \
पूर्ण

#घोषणा STRUCT_KFIFO_PTR(type) \
	काष्ठा __STRUCT_KFIFO_PTR(type, 0, type)

/*
 * define compatibility "struct kfifo" क्रम dynamic allocated fअगरos
 */
काष्ठा kfअगरo __STRUCT_KFIFO_PTR(अचिन्हित अक्षर, 0, व्योम);

#घोषणा STRUCT_KFIFO_REC_1(size) \
	काष्ठा __STRUCT_KFIFO(अचिन्हित अक्षर, size, 1, व्योम)

#घोषणा STRUCT_KFIFO_REC_2(size) \
	काष्ठा __STRUCT_KFIFO(अचिन्हित अक्षर, size, 2, व्योम)

/*
 * define kfअगरo_rec types
 */
काष्ठा kfअगरo_rec_ptr_1 __STRUCT_KFIFO_PTR(अचिन्हित अक्षर, 1, व्योम);
काष्ठा kfअगरo_rec_ptr_2 __STRUCT_KFIFO_PTR(अचिन्हित अक्षर, 2, व्योम);

/*
 * helper macro to distinguish between real in place fअगरo where the fअगरo
 * array is a part of the काष्ठाure and the fअगरo type where the array is
 * outside of the fअगरo काष्ठाure.
 */
#घोषणा	__is_kfअगरo_ptr(fअगरo) \
	(माप(*fअगरo) == माप(STRUCT_KFIFO_PTR(typeof(*(fअगरo)->type))))

/**
 * DECLARE_KFIFO_PTR - macro to declare a fअगरo poपूर्णांकer object
 * @fअगरo: name of the declared fअगरo
 * @type: type of the fअगरo elements
 */
#घोषणा DECLARE_KFIFO_PTR(fअगरo, type)	STRUCT_KFIFO_PTR(type) fअगरo

/**
 * DECLARE_KFIFO - macro to declare a fअगरo object
 * @fअगरo: name of the declared fअगरo
 * @type: type of the fअगरo elements
 * @size: the number of elements in the fअगरo, this must be a घातer of 2
 */
#घोषणा DECLARE_KFIFO(fअगरo, type, size)	STRUCT_KFIFO(type, size) fअगरo

/**
 * INIT_KFIFO - Initialize a fअगरo declared by DECLARE_KFIFO
 * @fअगरo: name of the declared fअगरo datatype
 */
#घोषणा INIT_KFIFO(fअगरo) \
(व्योम)(अणु \
	typeof(&(fअगरo)) __पंचांगp = &(fअगरo); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	__kfअगरo->in = 0; \
	__kfअगरo->out = 0; \
	__kfअगरo->mask = __is_kfअगरo_ptr(__पंचांगp) ? 0 : ARRAY_SIZE(__पंचांगp->buf) - 1;\
	__kfअगरo->esize = माप(*__पंचांगp->buf); \
	__kfअगरo->data = __is_kfअगरo_ptr(__पंचांगp) ?  शून्य : __पंचांगp->buf; \
पूर्ण)

/**
 * DEFINE_KFIFO - macro to define and initialize a fअगरo
 * @fअगरo: name of the declared fअगरo datatype
 * @type: type of the fअगरo elements
 * @size: the number of elements in the fअगरo, this must be a घातer of 2
 *
 * Note: the macro can be used क्रम global and local fअगरo data type variables.
 */
#घोषणा DEFINE_KFIFO(fअगरo, type, size) \
	DECLARE_KFIFO(fअगरo, type, size) = \
	(typeof(fअगरo)) अणु \
		अणु \
			अणु \
			.in	= 0, \
			.out	= 0, \
			.mask	= __is_kfअगरo_ptr(&(fअगरo)) ? \
				  0 : \
				  ARRAY_SIZE((fअगरo).buf) - 1, \
			.esize	= माप(*(fअगरo).buf), \
			.data	= __is_kfअगरo_ptr(&(fअगरo)) ? \
				शून्य : \
				(fअगरo).buf, \
			पूर्ण \
		पूर्ण \
	पूर्ण


अटल अंतरभूत अचिन्हित पूर्णांक __must_check
__kfअगरo_uपूर्णांक_must_check_helper(अचिन्हित पूर्णांक val)
अणु
	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check
__kfअगरo_पूर्णांक_must_check_helper(पूर्णांक val)
अणु
	वापस val;
पूर्ण

/**
 * kfअगरo_initialized - Check अगर the fअगरo is initialized
 * @fअगरo: address of the fअगरo to check
 *
 * Return %true अगर fअगरo is initialized, otherwise %false.
 * Assumes the fअगरo was 0 beक्रमe.
 */
#घोषणा kfअगरo_initialized(fअगरo) ((fअगरo)->kfअगरo.mask)

/**
 * kfअगरo_esize - वापसs the size of the element managed by the fअगरo
 * @fअगरo: address of the fअगरo to be used
 */
#घोषणा kfअगरo_esize(fअगरo)	((fअगरo)->kfअगरo.esize)

/**
 * kfअगरo_recsize - वापसs the size of the record length field
 * @fअगरo: address of the fअगरo to be used
 */
#घोषणा kfअगरo_recsize(fअगरo)	(माप(*(fअगरo)->rectype))

/**
 * kfअगरo_size - वापसs the size of the fअगरo in elements
 * @fअगरo: address of the fअगरo to be used
 */
#घोषणा kfअगरo_size(fअगरo)	((fअगरo)->kfअगरo.mask + 1)

/**
 * kfअगरo_reset - हटाओs the entire fअगरo content
 * @fअगरo: address of the fअगरo to be used
 *
 * Note: usage of kfअगरo_reset() is dangerous. It should be only called when the
 * fअगरo is exclusived locked or when it is secured that no other thपढ़ो is
 * accessing the fअगरo.
 */
#घोषणा kfअगरo_reset(fअगरo) \
(व्योम)(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	__पंचांगp->kfअगरo.in = __पंचांगp->kfअगरo.out = 0; \
पूर्ण)

/**
 * kfअगरo_reset_out - skip fअगरo content
 * @fअगरo: address of the fअगरo to be used
 *
 * Note: The usage of kfअगरo_reset_out() is safe until it will be only called
 * from the पढ़ोer thपढ़ो and there is only one concurrent पढ़ोer. Otherwise
 * it is dangerous and must be handled in the same way as kfअगरo_reset().
 */
#घोषणा kfअगरo_reset_out(fअगरo)	\
(व्योम)(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	__पंचांगp->kfअगरo.out = __पंचांगp->kfअगरo.in; \
पूर्ण)

/**
 * kfअगरo_len - वापसs the number of used elements in the fअगरo
 * @fअगरo: address of the fअगरo to be used
 */
#घोषणा kfअगरo_len(fअगरo) \
(अणु \
	typeof((fअगरo) + 1) __पंचांगpl = (fअगरo); \
	__पंचांगpl->kfअगरo.in - __पंचांगpl->kfअगरo.out; \
पूर्ण)

/**
 * kfअगरo_is_empty - वापसs true अगर the fअगरo is empty
 * @fअगरo: address of the fअगरo to be used
 */
#घोषणा	kfअगरo_is_empty(fअगरo) \
(अणु \
	typeof((fअगरo) + 1) __पंचांगpq = (fअगरo); \
	__पंचांगpq->kfअगरo.in == __पंचांगpq->kfअगरo.out; \
पूर्ण)

/**
 * kfअगरo_is_empty_spinlocked - वापसs true अगर the fअगरo is empty using
 * a spinlock क्रम locking
 * @fअगरo: address of the fअगरo to be used
 * @lock: spinlock to be used क्रम locking
 */
#घोषणा kfअगरo_is_empty_spinlocked(fअगरo, lock) \
(अणु \
	अचिन्हित दीर्घ __flags; \
	bool __ret; \
	spin_lock_irqsave(lock, __flags); \
	__ret = kfअगरo_is_empty(fअगरo); \
	spin_unlock_irqrestore(lock, __flags); \
	__ret; \
पूर्ण)

/**
 * kfअगरo_is_empty_spinlocked_noirqsave  - वापसs true अगर the fअगरo is empty
 * using a spinlock क्रम locking, करोesn't disable पूर्णांकerrupts
 * @fअगरo: address of the fअगरo to be used
 * @lock: spinlock to be used क्रम locking
 */
#घोषणा kfअगरo_is_empty_spinlocked_noirqsave(fअगरo, lock) \
(अणु \
	bool __ret; \
	spin_lock(lock); \
	__ret = kfअगरo_is_empty(fअगरo); \
	spin_unlock(lock); \
	__ret; \
पूर्ण)

/**
 * kfअगरo_is_full - वापसs true अगर the fअगरo is full
 * @fअगरo: address of the fअगरo to be used
 */
#घोषणा	kfअगरo_is_full(fअगरo) \
(अणु \
	typeof((fअगरo) + 1) __पंचांगpq = (fअगरo); \
	kfअगरo_len(__पंचांगpq) > __पंचांगpq->kfअगरo.mask; \
पूर्ण)

/**
 * kfअगरo_avail - वापसs the number of unused elements in the fअगरo
 * @fअगरo: address of the fअगरo to be used
 */
#घोषणा	kfअगरo_avail(fअगरo) \
__kfअगरo_uपूर्णांक_must_check_helper( \
(अणु \
	typeof((fअगरo) + 1) __पंचांगpq = (fअगरo); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगpq->rectype); \
	अचिन्हित पूर्णांक __avail = kfअगरo_size(__पंचांगpq) - kfअगरo_len(__पंचांगpq); \
	(__recsize) ? ((__avail <= __recsize) ? 0 : \
	__kfअगरo_max_r(__avail - __recsize, __recsize)) : \
	__avail; \
पूर्ण) \
)

/**
 * kfअगरo_skip - skip output data
 * @fअगरo: address of the fअगरo to be used
 */
#घोषणा	kfअगरo_skip(fअगरo) \
(व्योम)(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	अगर (__recsize) \
		__kfअगरo_skip_r(__kfअगरo, __recsize); \
	अन्यथा \
		__kfअगरo->out++; \
पूर्ण)

/**
 * kfअगरo_peek_len - माला_लो the size of the next fअगरo record
 * @fअगरo: address of the fअगरo to be used
 *
 * This function वापसs the size of the next fअगरo record in number of bytes.
 */
#घोषणा kfअगरo_peek_len(fअगरo) \
__kfअगरo_uपूर्णांक_must_check_helper( \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	(!__recsize) ? kfअगरo_len(__पंचांगp) * माप(*__पंचांगp->type) : \
	__kfअगरo_len_r(__kfअगरo, __recsize); \
पूर्ण) \
)

/**
 * kfअगरo_alloc - dynamically allocates a new fअगरo buffer
 * @fअगरo: poपूर्णांकer to the fअगरo
 * @size: the number of elements in the fअगरo, this must be a घातer of 2
 * @gfp_mask: get_मुक्त_pages mask, passed to kदो_स्मृति()
 *
 * This macro dynamically allocates a new fअगरo buffer.
 *
 * The number of elements will be rounded-up to a घातer of 2.
 * The fअगरo will be release with kfअगरo_मुक्त().
 * Return 0 अगर no error, otherwise an error code.
 */
#घोषणा kfअगरo_alloc(fअगरo, size, gfp_mask) \
__kfअगरo_पूर्णांक_must_check_helper( \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	__is_kfअगरo_ptr(__पंचांगp) ? \
	__kfअगरo_alloc(__kfअगरo, size, माप(*__पंचांगp->type), gfp_mask) : \
	-EINVAL; \
पूर्ण) \
)

/**
 * kfअगरo_मुक्त - मुक्तs the fअगरo
 * @fअगरo: the fअगरo to be मुक्तd
 */
#घोषणा kfअगरo_मुक्त(fअगरo) \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	अगर (__is_kfअगरo_ptr(__पंचांगp)) \
		__kfअगरo_मुक्त(__kfअगरo); \
पूर्ण)

/**
 * kfअगरo_init - initialize a fअगरo using a pपुनः_स्मृतिated buffer
 * @fअगरo: the fअगरo to assign the buffer
 * @buffer: the pपुनः_स्मृतिated buffer to be used
 * @size: the size of the पूर्णांकernal buffer, this have to be a घातer of 2
 *
 * This macro initializes a fअगरo using a pपुनः_स्मृतिated buffer.
 *
 * The number of elements will be rounded-up to a घातer of 2.
 * Return 0 अगर no error, otherwise an error code.
 */
#घोषणा kfअगरo_init(fअगरo, buffer, size) \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	__is_kfअगरo_ptr(__पंचांगp) ? \
	__kfअगरo_init(__kfअगरo, buffer, size, माप(*__पंचांगp->type)) : \
	-EINVAL; \
पूर्ण)

/**
 * kfअगरo_put - put data पूर्णांकo the fअगरo
 * @fअगरo: address of the fअगरo to be used
 * @val: the data to be added
 *
 * This macro copies the given value पूर्णांकo the fअगरo.
 * It वापसs 0 अगर the fअगरo was full. Otherwise it वापसs the number
 * processed elements.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macro.
 */
#घोषणा	kfअगरo_put(fअगरo, val) \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	typeof(*__पंचांगp->स्थिर_type) __val = (val); \
	अचिन्हित पूर्णांक __ret; \
	माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	अगर (__recsize) \
		__ret = __kfअगरo_in_r(__kfअगरo, &__val, माप(__val), \
			__recsize); \
	अन्यथा अणु \
		__ret = !kfअगरo_is_full(__पंचांगp); \
		अगर (__ret) अणु \
			(__is_kfअगरo_ptr(__पंचांगp) ? \
			((typeof(__पंचांगp->type))__kfअगरo->data) : \
			(__पंचांगp->buf) \
			)[__kfअगरo->in & __पंचांगp->kfअगरo.mask] = \
				*(typeof(__पंचांगp->type))&__val; \
			smp_wmb(); \
			__kfअगरo->in++; \
		पूर्ण \
	पूर्ण \
	__ret; \
पूर्ण)

/**
 * kfअगरo_get - get data from the fअगरo
 * @fअगरo: address of the fअगरo to be used
 * @val: address where to store the data
 *
 * This macro पढ़ोs the data from the fअगरo.
 * It वापसs 0 अगर the fअगरo was empty. Otherwise it वापसs the number
 * processed elements.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macro.
 */
#घोषणा	kfअगरo_get(fअगरo, val) \
__kfअगरo_uपूर्णांक_must_check_helper( \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	typeof(__पंचांगp->ptr) __val = (val); \
	अचिन्हित पूर्णांक __ret; \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	अगर (__recsize) \
		__ret = __kfअगरo_out_r(__kfअगरo, __val, माप(*__val), \
			__recsize); \
	अन्यथा अणु \
		__ret = !kfअगरo_is_empty(__पंचांगp); \
		अगर (__ret) अणु \
			*(typeof(__पंचांगp->type))__val = \
				(__is_kfअगरo_ptr(__पंचांगp) ? \
				((typeof(__पंचांगp->type))__kfअगरo->data) : \
				(__पंचांगp->buf) \
				)[__kfअगरo->out & __पंचांगp->kfअगरo.mask]; \
			smp_wmb(); \
			__kfअगरo->out++; \
		पूर्ण \
	पूर्ण \
	__ret; \
पूर्ण) \
)

/**
 * kfअगरo_peek - get data from the fअगरo without removing
 * @fअगरo: address of the fअगरo to be used
 * @val: address where to store the data
 *
 * This पढ़ोs the data from the fअगरo without removing it from the fअगरo.
 * It वापसs 0 अगर the fअगरo was empty. Otherwise it वापसs the number
 * processed elements.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macro.
 */
#घोषणा	kfअगरo_peek(fअगरo, val) \
__kfअगरo_uपूर्णांक_must_check_helper( \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	typeof(__पंचांगp->ptr) __val = (val); \
	अचिन्हित पूर्णांक __ret; \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	अगर (__recsize) \
		__ret = __kfअगरo_out_peek_r(__kfअगरo, __val, माप(*__val), \
			__recsize); \
	अन्यथा अणु \
		__ret = !kfअगरo_is_empty(__पंचांगp); \
		अगर (__ret) अणु \
			*(typeof(__पंचांगp->type))__val = \
				(__is_kfअगरo_ptr(__पंचांगp) ? \
				((typeof(__पंचांगp->type))__kfअगरo->data) : \
				(__पंचांगp->buf) \
				)[__kfअगरo->out & __पंचांगp->kfअगरo.mask]; \
			smp_wmb(); \
		पूर्ण \
	पूर्ण \
	__ret; \
पूर्ण) \
)

/**
 * kfअगरo_in - put data पूर्णांकo the fअगरo
 * @fअगरo: address of the fअगरo to be used
 * @buf: the data to be added
 * @n: number of elements to be added
 *
 * This macro copies the given buffer पूर्णांकo the fअगरo and वापसs the
 * number of copied elements.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macro.
 */
#घोषणा	kfअगरo_in(fअगरo, buf, n) \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	typeof(__पंचांगp->ptr_स्थिर) __buf = (buf); \
	अचिन्हित दीर्घ __n = (n); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	(__recsize) ?\
	__kfअगरo_in_r(__kfअगरo, __buf, __n, __recsize) : \
	__kfअगरo_in(__kfअगरo, __buf, __n); \
पूर्ण)

/**
 * kfअगरo_in_spinlocked - put data पूर्णांकo the fअगरo using a spinlock क्रम locking
 * @fअगरo: address of the fअगरo to be used
 * @buf: the data to be added
 * @n: number of elements to be added
 * @lock: poपूर्णांकer to the spinlock to use क्रम locking
 *
 * This macro copies the given values buffer पूर्णांकo the fअगरo and वापसs the
 * number of copied elements.
 */
#घोषणा	kfअगरo_in_spinlocked(fअगरo, buf, n, lock) \
(अणु \
	अचिन्हित दीर्घ __flags; \
	अचिन्हित पूर्णांक __ret; \
	spin_lock_irqsave(lock, __flags); \
	__ret = kfअगरo_in(fअगरo, buf, n); \
	spin_unlock_irqrestore(lock, __flags); \
	__ret; \
पूर्ण)

/**
 * kfअगरo_in_spinlocked_noirqsave - put data पूर्णांकo fअगरo using a spinlock क्रम
 * locking, करोn't disable पूर्णांकerrupts
 * @fअगरo: address of the fअगरo to be used
 * @buf: the data to be added
 * @n: number of elements to be added
 * @lock: poपूर्णांकer to the spinlock to use क्रम locking
 *
 * This is a variant of kfअगरo_in_spinlocked() but uses spin_lock/unlock()
 * क्रम locking and करोesn't disable पूर्णांकerrupts.
 */
#घोषणा kfअगरo_in_spinlocked_noirqsave(fअगरo, buf, n, lock) \
(अणु \
	अचिन्हित पूर्णांक __ret; \
	spin_lock(lock); \
	__ret = kfअगरo_in(fअगरo, buf, n); \
	spin_unlock(lock); \
	__ret; \
पूर्ण)

/* alias क्रम kfअगरo_in_spinlocked, will be हटाओd in a future release */
#घोषणा kfअगरo_in_locked(fअगरo, buf, n, lock) \
		kfअगरo_in_spinlocked(fअगरo, buf, n, lock)

/**
 * kfअगरo_out - get data from the fअगरo
 * @fअगरo: address of the fअगरo to be used
 * @buf: poपूर्णांकer to the storage buffer
 * @n: max. number of elements to get
 *
 * This macro get some data from the fअगरo and वापस the numbers of elements
 * copied.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macro.
 */
#घोषणा	kfअगरo_out(fअगरo, buf, n) \
__kfअगरo_uपूर्णांक_must_check_helper( \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	typeof(__पंचांगp->ptr) __buf = (buf); \
	अचिन्हित दीर्घ __n = (n); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	(__recsize) ?\
	__kfअगरo_out_r(__kfअगरo, __buf, __n, __recsize) : \
	__kfअगरo_out(__kfअगरo, __buf, __n); \
पूर्ण) \
)

/**
 * kfअगरo_out_spinlocked - get data from the fअगरo using a spinlock क्रम locking
 * @fअगरo: address of the fअगरo to be used
 * @buf: poपूर्णांकer to the storage buffer
 * @n: max. number of elements to get
 * @lock: poपूर्णांकer to the spinlock to use क्रम locking
 *
 * This macro get the data from the fअगरo and वापस the numbers of elements
 * copied.
 */
#घोषणा	kfअगरo_out_spinlocked(fअगरo, buf, n, lock) \
__kfअगरo_uपूर्णांक_must_check_helper( \
(अणु \
	अचिन्हित दीर्घ __flags; \
	अचिन्हित पूर्णांक __ret; \
	spin_lock_irqsave(lock, __flags); \
	__ret = kfअगरo_out(fअगरo, buf, n); \
	spin_unlock_irqrestore(lock, __flags); \
	__ret; \
पूर्ण) \
)

/**
 * kfअगरo_out_spinlocked_noirqsave - get data from the fअगरo using a spinlock
 * क्रम locking, करोn't disable पूर्णांकerrupts
 * @fअगरo: address of the fअगरo to be used
 * @buf: poपूर्णांकer to the storage buffer
 * @n: max. number of elements to get
 * @lock: poपूर्णांकer to the spinlock to use क्रम locking
 *
 * This is a variant of kfअगरo_out_spinlocked() which uses spin_lock/unlock()
 * क्रम locking and करोesn't disable पूर्णांकerrupts.
 */
#घोषणा kfअगरo_out_spinlocked_noirqsave(fअगरo, buf, n, lock) \
__kfअगरo_uपूर्णांक_must_check_helper( \
(अणु \
	अचिन्हित पूर्णांक __ret; \
	spin_lock(lock); \
	__ret = kfअगरo_out(fअगरo, buf, n); \
	spin_unlock(lock); \
	__ret; \
पूर्ण) \
)

/* alias क्रम kfअगरo_out_spinlocked, will be हटाओd in a future release */
#घोषणा kfअगरo_out_locked(fअगरo, buf, n, lock) \
		kfअगरo_out_spinlocked(fअगरo, buf, n, lock)

/**
 * kfअगरo_from_user - माला_दो some data from user space पूर्णांकo the fअगरo
 * @fअगरo: address of the fअगरo to be used
 * @from: poपूर्णांकer to the data to be added
 * @len: the length of the data to be added
 * @copied: poपूर्णांकer to output variable to store the number of copied bytes
 *
 * This macro copies at most @len bytes from the @from पूर्णांकo the
 * fअगरo, depending of the available space and वापसs -EFAULT/0.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macro.
 */
#घोषणा	kfअगरo_from_user(fअगरo, from, len, copied) \
__kfअगरo_uपूर्णांक_must_check_helper( \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	स्थिर व्योम __user *__from = (from); \
	अचिन्हित पूर्णांक __len = (len); \
	अचिन्हित पूर्णांक *__copied = (copied); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	(__recsize) ? \
	__kfअगरo_from_user_r(__kfअगरo, __from, __len,  __copied, __recsize) : \
	__kfअगरo_from_user(__kfअगरo, __from, __len, __copied); \
पूर्ण) \
)

/**
 * kfअगरo_to_user - copies data from the fअगरo पूर्णांकo user space
 * @fअगरo: address of the fअगरo to be used
 * @to: where the data must be copied
 * @len: the size of the destination buffer
 * @copied: poपूर्णांकer to output variable to store the number of copied bytes
 *
 * This macro copies at most @len bytes from the fअगरo पूर्णांकo the
 * @to buffer and वापसs -EFAULT/0.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macro.
 */
#घोषणा	kfअगरo_to_user(fअगरo, to, len, copied) \
__kfअगरo_uपूर्णांक_must_check_helper( \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	व्योम __user *__to = (to); \
	अचिन्हित पूर्णांक __len = (len); \
	अचिन्हित पूर्णांक *__copied = (copied); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	(__recsize) ? \
	__kfअगरo_to_user_r(__kfअगरo, __to, __len, __copied, __recsize) : \
	__kfअगरo_to_user(__kfअगरo, __to, __len, __copied); \
पूर्ण) \
)

/**
 * kfअगरo_dma_in_prepare - setup a scatterlist क्रम DMA input
 * @fअगरo: address of the fअगरo to be used
 * @sgl: poपूर्णांकer to the scatterlist array
 * @nents: number of entries in the scatterlist array
 * @len: number of elements to transfer
 *
 * This macro fills a scatterlist क्रम DMA input.
 * It वापसs the number entries in the scatterlist array.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macros.
 */
#घोषणा	kfअगरo_dma_in_prepare(fअगरo, sgl, nents, len) \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	काष्ठा scatterlist *__sgl = (sgl); \
	पूर्णांक __nents = (nents); \
	अचिन्हित पूर्णांक __len = (len); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	(__recsize) ? \
	__kfअगरo_dma_in_prepare_r(__kfअगरo, __sgl, __nents, __len, __recsize) : \
	__kfअगरo_dma_in_prepare(__kfअगरo, __sgl, __nents, __len); \
पूर्ण)

/**
 * kfअगरo_dma_in_finish - finish a DMA IN operation
 * @fअगरo: address of the fअगरo to be used
 * @len: number of bytes to received
 *
 * This macro finish a DMA IN operation. The in counter will be updated by
 * the len parameter. No error checking will be करोne.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macros.
 */
#घोषणा kfअगरo_dma_in_finish(fअगरo, len) \
(व्योम)(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	अचिन्हित पूर्णांक __len = (len); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	अगर (__recsize) \
		__kfअगरo_dma_in_finish_r(__kfअगरo, __len, __recsize); \
	अन्यथा \
		__kfअगरo->in += __len / माप(*__पंचांगp->type); \
पूर्ण)

/**
 * kfअगरo_dma_out_prepare - setup a scatterlist क्रम DMA output
 * @fअगरo: address of the fअगरo to be used
 * @sgl: poपूर्णांकer to the scatterlist array
 * @nents: number of entries in the scatterlist array
 * @len: number of elements to transfer
 *
 * This macro fills a scatterlist क्रम DMA output which at most @len bytes
 * to transfer.
 * It वापसs the number entries in the scatterlist array.
 * A zero means there is no space available and the scatterlist is not filled.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macros.
 */
#घोषणा	kfअगरo_dma_out_prepare(fअगरo, sgl, nents, len) \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo);  \
	काष्ठा scatterlist *__sgl = (sgl); \
	पूर्णांक __nents = (nents); \
	अचिन्हित पूर्णांक __len = (len); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	(__recsize) ? \
	__kfअगरo_dma_out_prepare_r(__kfअगरo, __sgl, __nents, __len, __recsize) : \
	__kfअगरo_dma_out_prepare(__kfअगरo, __sgl, __nents, __len); \
पूर्ण)

/**
 * kfअगरo_dma_out_finish - finish a DMA OUT operation
 * @fअगरo: address of the fअगरo to be used
 * @len: number of bytes transferred
 *
 * This macro finish a DMA OUT operation. The out counter will be updated by
 * the len parameter. No error checking will be करोne.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macros.
 */
#घोषणा kfअगरo_dma_out_finish(fअगरo, len) \
(व्योम)(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	अचिन्हित पूर्णांक __len = (len); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	अगर (__recsize) \
		__kfअगरo_dma_out_finish_r(__kfअगरo, __recsize); \
	अन्यथा \
		__kfअगरo->out += __len / माप(*__पंचांगp->type); \
पूर्ण)

/**
 * kfअगरo_out_peek - माला_लो some data from the fअगरo
 * @fअगरo: address of the fअगरo to be used
 * @buf: poपूर्णांकer to the storage buffer
 * @n: max. number of elements to get
 *
 * This macro get the data from the fअगरo and वापस the numbers of elements
 * copied. The data is not हटाओd from the fअगरo.
 *
 * Note that with only one concurrent पढ़ोer and one concurrent
 * ग_लिखोr, you करोn't need extra locking to use these macro.
 */
#घोषणा	kfअगरo_out_peek(fअगरo, buf, n) \
__kfअगरo_uपूर्णांक_must_check_helper( \
(अणु \
	typeof((fअगरo) + 1) __पंचांगp = (fअगरo); \
	typeof(__पंचांगp->ptr) __buf = (buf); \
	अचिन्हित दीर्घ __n = (n); \
	स्थिर माप_प्रकार __recsize = माप(*__पंचांगp->rectype); \
	काष्ठा __kfअगरo *__kfअगरo = &__पंचांगp->kfअगरo; \
	(__recsize) ? \
	__kfअगरo_out_peek_r(__kfअगरo, __buf, __n, __recsize) : \
	__kfअगरo_out_peek(__kfअगरo, __buf, __n); \
पूर्ण) \
)

बाह्य पूर्णांक __kfअगरo_alloc(काष्ठा __kfअगरo *fअगरo, अचिन्हित पूर्णांक size,
	माप_प्रकार esize, gfp_t gfp_mask);

बाह्य व्योम __kfअगरo_मुक्त(काष्ठा __kfअगरo *fअगरo);

बाह्य पूर्णांक __kfअगरo_init(काष्ठा __kfअगरo *fअगरo, व्योम *buffer,
	अचिन्हित पूर्णांक size, माप_प्रकार esize);

बाह्य अचिन्हित पूर्णांक __kfअगरo_in(काष्ठा __kfअगरo *fअगरo,
	स्थिर व्योम *buf, अचिन्हित पूर्णांक len);

बाह्य अचिन्हित पूर्णांक __kfअगरo_out(काष्ठा __kfअगरo *fअगरo,
	व्योम *buf, अचिन्हित पूर्णांक len);

बाह्य पूर्णांक __kfअगरo_from_user(काष्ठा __kfअगरo *fअगरo,
	स्थिर व्योम __user *from, अचिन्हित दीर्घ len, अचिन्हित पूर्णांक *copied);

बाह्य पूर्णांक __kfअगरo_to_user(काष्ठा __kfअगरo *fअगरo,
	व्योम __user *to, अचिन्हित दीर्घ len, अचिन्हित पूर्णांक *copied);

बाह्य अचिन्हित पूर्णांक __kfअगरo_dma_in_prepare(काष्ठा __kfअगरo *fअगरo,
	काष्ठा scatterlist *sgl, पूर्णांक nents, अचिन्हित पूर्णांक len);

बाह्य अचिन्हित पूर्णांक __kfअगरo_dma_out_prepare(काष्ठा __kfअगरo *fअगरo,
	काष्ठा scatterlist *sgl, पूर्णांक nents, अचिन्हित पूर्णांक len);

बाह्य अचिन्हित पूर्णांक __kfअगरo_out_peek(काष्ठा __kfअगरo *fअगरo,
	व्योम *buf, अचिन्हित पूर्णांक len);

बाह्य अचिन्हित पूर्णांक __kfअगरo_in_r(काष्ठा __kfअगरo *fअगरo,
	स्थिर व्योम *buf, अचिन्हित पूर्णांक len, माप_प्रकार recsize);

बाह्य अचिन्हित पूर्णांक __kfअगरo_out_r(काष्ठा __kfअगरo *fअगरo,
	व्योम *buf, अचिन्हित पूर्णांक len, माप_प्रकार recsize);

बाह्य पूर्णांक __kfअगरo_from_user_r(काष्ठा __kfअगरo *fअगरo,
	स्थिर व्योम __user *from, अचिन्हित दीर्घ len, अचिन्हित पूर्णांक *copied,
	माप_प्रकार recsize);

बाह्य पूर्णांक __kfअगरo_to_user_r(काष्ठा __kfअगरo *fअगरo, व्योम __user *to,
	अचिन्हित दीर्घ len, अचिन्हित पूर्णांक *copied, माप_प्रकार recsize);

बाह्य अचिन्हित पूर्णांक __kfअगरo_dma_in_prepare_r(काष्ठा __kfअगरo *fअगरo,
	काष्ठा scatterlist *sgl, पूर्णांक nents, अचिन्हित पूर्णांक len, माप_प्रकार recsize);

बाह्य व्योम __kfअगरo_dma_in_finish_r(काष्ठा __kfअगरo *fअगरo,
	अचिन्हित पूर्णांक len, माप_प्रकार recsize);

बाह्य अचिन्हित पूर्णांक __kfअगरo_dma_out_prepare_r(काष्ठा __kfअगरo *fअगरo,
	काष्ठा scatterlist *sgl, पूर्णांक nents, अचिन्हित पूर्णांक len, माप_प्रकार recsize);

बाह्य व्योम __kfअगरo_dma_out_finish_r(काष्ठा __kfअगरo *fअगरo, माप_प्रकार recsize);

बाह्य अचिन्हित पूर्णांक __kfअगरo_len_r(काष्ठा __kfअगरo *fअगरo, माप_प्रकार recsize);

बाह्य व्योम __kfअगरo_skip_r(काष्ठा __kfअगरo *fअगरo, माप_प्रकार recsize);

बाह्य अचिन्हित पूर्णांक __kfअगरo_out_peek_r(काष्ठा __kfअगरo *fअगरo,
	व्योम *buf, अचिन्हित पूर्णांक len, माप_प्रकार recsize);

बाह्य अचिन्हित पूर्णांक __kfअगरo_max_r(अचिन्हित पूर्णांक len, माप_प्रकार recsize);

#पूर्ण_अगर
