<शैली गुरु>
/*
 * Public header क्रम the MPC52xx processor BestComm driver
 *
 *
 * Copyright (C) 2006      Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2005      Varma Electronics Oy,
 *                         ( by Andrey Volkov <avolkov@varma-el.com> )
 * Copyright (C) 2003-2004 MontaVista, Software, Inc.
 *                         ( by Dale Farnsworth <dfarnsworth@mvista.com> )
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित __BESTCOMM_H__
#घोषणा __BESTCOMM_H__

/**
 * काष्ठा bcom_bd - Structure describing a generic BestComm buffer descriptor
 * @status: The current status of this buffer. Exact meaning depends on the
 *          task type
 * @data: An array of u32 extra data.  Size of array is task dependent.
 *
 * Note: Don't dereference a bcom_bd poपूर्णांकer as an array.  The size of the
 *       bcom_bd is variable.  Use bcom_get_bd() instead.
 */
काष्ठा bcom_bd अणु
	u32	status;
	u32	data[];	/* variable payload size */
पूर्ण;

/* ======================================================================== */
/* Generic task management                                                   */
/* ======================================================================== */

/**
 * काष्ठा bcom_task - Structure describing a loaded BestComm task
 *
 * This काष्ठाure is never built by the driver it self. It's built and
 * filled the पूर्णांकermediate layer of the BestComm API, the task dependent
 * support code.
 *
 * Most likely you करोn't need to poke around inside this काष्ठाure. The
 * fields are exposed in the header just क्रम the sake of अंतरभूत functions
 */
काष्ठा bcom_task अणु
	अचिन्हित पूर्णांक	tasknum;
	अचिन्हित पूर्णांक	flags;
	पूर्णांक		irq;

	काष्ठा bcom_bd	*bd;
	phys_addr_t	bd_pa;
	व्योम		**cookie;
	अचिन्हित लघु	index;
	अचिन्हित लघु	outdex;
	अचिन्हित पूर्णांक	num_bd;
	अचिन्हित पूर्णांक	bd_size;

	व्योम*		priv;
पूर्ण;

#घोषणा BCOM_FLAGS_NONE         0x00000000ul
#घोषणा BCOM_FLAGS_ENABLE_TASK  (1ul <<  0)

/**
 * bcom_enable - Enable a BestComm task
 * @tsk: The BestComm task काष्ठाure
 *
 * This function makes sure the given task is enabled and can be run
 * by the BestComm engine as needed
 */
बाह्य व्योम bcom_enable(काष्ठा bcom_task *tsk);

/**
 * bcom_disable - Disable a BestComm task
 * @tsk: The BestComm task काष्ठाure
 *
 * This function disable a given task, making sure it's not executed
 * by the BestComm engine.
 */
बाह्य व्योम bcom_disable(काष्ठा bcom_task *tsk);


/**
 * bcom_get_task_irq - Returns the irq number of a BestComm task
 * @tsk: The BestComm task काष्ठाure
 */
अटल अंतरभूत पूर्णांक
bcom_get_task_irq(काष्ठा bcom_task *tsk) अणु
	वापस tsk->irq;
पूर्ण

/* ======================================================================== */
/* BD based tasks helpers                                                   */
/* ======================================================================== */

#घोषणा BCOM_BD_READY	0x40000000ul

/** _bcom_next_index - Get next input index.
 * @tsk: poपूर्णांकer to task काष्ठाure
 *
 * Support function; Device drivers should not call this
 */
अटल अंतरभूत पूर्णांक
_bcom_next_index(काष्ठा bcom_task *tsk)
अणु
	वापस ((tsk->index + 1) == tsk->num_bd) ? 0 : tsk->index + 1;
पूर्ण

/** _bcom_next_outdex - Get next output index.
 * @tsk: poपूर्णांकer to task काष्ठाure
 *
 * Support function; Device drivers should not call this
 */
अटल अंतरभूत पूर्णांक
_bcom_next_outdex(काष्ठा bcom_task *tsk)
अणु
	वापस ((tsk->outdex + 1) == tsk->num_bd) ? 0 : tsk->outdex + 1;
पूर्ण

/**
 * bcom_queue_empty - Checks अगर a BestComm task BD queue is empty
 * @tsk: The BestComm task काष्ठाure
 */
अटल अंतरभूत पूर्णांक
bcom_queue_empty(काष्ठा bcom_task *tsk)
अणु
	वापस tsk->index == tsk->outdex;
पूर्ण

/**
 * bcom_queue_full - Checks अगर a BestComm task BD queue is full
 * @tsk: The BestComm task काष्ठाure
 */
अटल अंतरभूत पूर्णांक
bcom_queue_full(काष्ठा bcom_task *tsk)
अणु
	वापस tsk->outdex == _bcom_next_index(tsk);
पूर्ण

/**
 * bcom_get_bd - Get a BD from the queue
 * @tsk: The BestComm task काष्ठाure
 * index: Index of the BD to fetch
 */
अटल अंतरभूत काष्ठा bcom_bd
*bcom_get_bd(काष्ठा bcom_task *tsk, अचिन्हित पूर्णांक index)
अणु
	/* A cast to (व्योम*) so the address can be incremented by the
	 * real size instead of by माप(काष्ठा bcom_bd) */
	वापस ((व्योम *)tsk->bd) + (index * tsk->bd_size);
पूर्ण

/**
 * bcom_buffer_करोne - Checks अगर a BestComm 
 * @tsk: The BestComm task काष्ठाure
 */
अटल अंतरभूत पूर्णांक
bcom_buffer_करोne(काष्ठा bcom_task *tsk)
अणु
	काष्ठा bcom_bd *bd;
	अगर (bcom_queue_empty(tsk))
		वापस 0;

	bd = bcom_get_bd(tsk, tsk->outdex);
	वापस !(bd->status & BCOM_BD_READY);
पूर्ण

/**
 * bcom_prepare_next_buffer - clear status of next available buffer.
 * @tsk: The BestComm task काष्ठाure
 *
 * Returns poपूर्णांकer to next buffer descriptor
 */
अटल अंतरभूत काष्ठा bcom_bd *
bcom_prepare_next_buffer(काष्ठा bcom_task *tsk)
अणु
	काष्ठा bcom_bd *bd;

	bd = bcom_get_bd(tsk, tsk->index);
	bd->status = 0;	/* cleanup last status */
	वापस bd;
पूर्ण

अटल अंतरभूत व्योम
bcom_submit_next_buffer(काष्ठा bcom_task *tsk, व्योम *cookie)
अणु
	काष्ठा bcom_bd *bd = bcom_get_bd(tsk, tsk->index);

	tsk->cookie[tsk->index] = cookie;
	mb();	/* ensure the bd is really up-to-date */
	bd->status |= BCOM_BD_READY;
	tsk->index = _bcom_next_index(tsk);
	अगर (tsk->flags & BCOM_FLAGS_ENABLE_TASK)
		bcom_enable(tsk);
पूर्ण

अटल अंतरभूत व्योम *
bcom_retrieve_buffer(काष्ठा bcom_task *tsk, u32 *p_status, काष्ठा bcom_bd **p_bd)
अणु
	व्योम *cookie = tsk->cookie[tsk->outdex];
	काष्ठा bcom_bd *bd = bcom_get_bd(tsk, tsk->outdex);

	अगर (p_status)
		*p_status = bd->status;
	अगर (p_bd)
		*p_bd = bd;
	tsk->outdex = _bcom_next_outdex(tsk);
	वापस cookie;
पूर्ण

#पूर्ण_अगर /* __BESTCOMM_H__ */
