<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*****************************************************************************
 * xenbus.h
 *
 * Xenbus protocol details.
 *
 * Copyright (C) 2005 XenSource Ltd.
 */

#अगर_अघोषित _XEN_PUBLIC_IO_XENBUS_H
#घोषणा _XEN_PUBLIC_IO_XENBUS_H

/* The state of either end of the Xenbus, i.e. the current communication
   status of initialisation across the bus.  States here imply nothing about
   the state of the connection between the driver and the kernel's device
   layers.  */
क्रमागत xenbus_state
अणु
	XenbusStateUnknown      = 0,
	XenbusStateInitialising = 1,
	XenbusStateInitWait     = 2,  /* Finished early
					 initialisation, but रुकोing
					 क्रम inक्रमmation from the peer
					 or hotplug scripts. */
	XenbusStateInitialised  = 3,  /* Initialised and रुकोing क्रम a
					 connection from the peer. */
	XenbusStateConnected    = 4,
	XenbusStateClosing      = 5,  /* The device is being बंदd
					 due to an error or an unplug
					 event. */
	XenbusStateClosed       = 6,

	/*
	* Reconfiguring: The device is being reconfigured.
	*/
	XenbusStateReconfiguring = 7,

	XenbusStateReconfigured  = 8
पूर्ण;

#पूर्ण_अगर /* _XEN_PUBLIC_IO_XENBUS_H */
