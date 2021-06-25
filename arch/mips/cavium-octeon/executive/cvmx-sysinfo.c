<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2008 Cavium Networks
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

/*
 * This module provides प्रणाली/board/application inक्रमmation obtained
 * by the bootloader.
 */
#समावेश <linux/export.h>

#समावेश <यंत्र/octeon/cvmx.h>
#समावेश <यंत्र/octeon/cvmx-sysinfo.h>

/*
 * This काष्ठाure defines the निजी state मुख्यtained by sysinfo module.
 */
अटल काष्ठा cvmx_sysinfo sysinfo;	   /* प्रणाली inक्रमmation */

/*
 * Returns the application inक्रमmation as obtained
 * by the bootloader.  This provides the core mask of the cores
 * running the same application image, as well as the physical
 * memory regions available to the core.
 */
काष्ठा cvmx_sysinfo *cvmx_sysinfo_get(व्योम)
अणु
	वापस &sysinfo;
पूर्ण
EXPORT_SYMBOL(cvmx_sysinfo_get);

