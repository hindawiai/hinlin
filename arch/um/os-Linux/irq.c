<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 - Cambridge Greys Ltd
 * Copyright (C) 2011 - 2014 Cisco Systems Inc
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/epoll.h>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <irq_user.h>
#समावेश <os.h>
#समावेश <um_दो_स्मृति.h>

/* Epoll support */

अटल पूर्णांक epollfd = -1;

#घोषणा MAX_EPOLL_EVENTS 64

अटल काष्ठा epoll_event epoll_events[MAX_EPOLL_EVENTS];

/* Helper to वापस an Epoll data poपूर्णांकer from an epoll event काष्ठाure.
 * We need to keep this one on the userspace side to keep includes separate
 */

व्योम *os_epoll_get_data_poपूर्णांकer(पूर्णांक index)
अणु
	वापस epoll_events[index].data.ptr;
पूर्ण

/* Helper to compare events versus the events in the epoll काष्ठाure.
 * Same as above - needs to be on the userspace side
 */


पूर्णांक os_epoll_triggered(पूर्णांक index, पूर्णांक events)
अणु
	वापस epoll_events[index].events & events;
पूर्ण
/* Helper to set the event mask.
 * The event mask is opaque to the kernel side, because it करोes not have
 * access to the right includes/defines क्रम EPOLL स्थिरants.
 */

पूर्णांक os_event_mask(क्रमागत um_irq_type irq_type)
अणु
	अगर (irq_type == IRQ_READ)
		वापस EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP | EPOLLRDHUP;
	अगर (irq_type == IRQ_WRITE)
		वापस EPOLLOUT;
	वापस 0;
पूर्ण

/*
 * Initial Epoll Setup
 */
पूर्णांक os_setup_epoll(व्योम)
अणु
	epollfd = epoll_create(MAX_EPOLL_EVENTS);
	वापस epollfd;
पूर्ण

/*
 * Helper to run the actual epoll_रुको
 */
पूर्णांक os_रुकोing_क्रम_events_epoll(व्योम)
अणु
	पूर्णांक n, err;

	n = epoll_रुको(epollfd,
		(काष्ठा epoll_event *) &epoll_events, MAX_EPOLL_EVENTS, 0);
	अगर (n < 0) अणु
		err = -त्रुटि_सं;
		अगर (त्रुटि_सं != EINTR)
			prपूर्णांकk(
				UM_KERN_ERR "os_waiting_for_events:"
				" epoll returned %d, error = %s\n", n,
				म_त्रुटि(त्रुटि_सं)
			);
		वापस err;
	पूर्ण
	वापस n;
पूर्ण


/*
 * Helper to add a fd to epoll
 */
पूर्णांक os_add_epoll_fd(पूर्णांक events, पूर्णांक fd, व्योम *data)
अणु
	काष्ठा epoll_event event;
	पूर्णांक result;

	event.data.ptr = data;
	event.events = events | EPOLLET;
	result = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	अगर ((result) && (त्रुटि_सं == EEXIST))
		result = os_mod_epoll_fd(events, fd, data);
	अगर (result)
		prपूर्णांकk("epollctl add err fd %d, %s\n", fd, म_त्रुटि(त्रुटि_सं));
	वापस result;
पूर्ण

/*
 * Helper to mod the fd event mask and/or data backreference
 */
पूर्णांक os_mod_epoll_fd(पूर्णांक events, पूर्णांक fd, व्योम *data)
अणु
	काष्ठा epoll_event event;
	पूर्णांक result;

	event.data.ptr = data;
	event.events = events;
	result = epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
	अगर (result)
		prपूर्णांकk(UM_KERN_ERR
			"epollctl mod err fd %d, %s\n", fd, म_त्रुटि(त्रुटि_सं));
	वापस result;
पूर्ण

/*
 * Helper to delete the epoll fd
 */
पूर्णांक os_del_epoll_fd(पूर्णांक fd)
अणु
	काष्ठा epoll_event event;
	पूर्णांक result;
	/* This is quiet as we use this as IO ON/OFF - so it is often
	 * invoked on a non-existent fd
	 */
	result = epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event);
	वापस result;
पूर्ण

व्योम os_set_ioignore(व्योम)
अणु
	संकेत(SIGIO, संक_छोड़ो);
पूर्ण

व्योम os_बंद_epoll_fd(व्योम)
अणु
	/* Needed so we करो not leak an fd when rebooting */
	os_बंद_file(epollfd);
पूर्ण
