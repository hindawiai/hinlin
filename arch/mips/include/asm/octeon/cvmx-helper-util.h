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
 *
 * Small helper utilities.
 *
 */

#अगर_अघोषित __CVMX_HELPER_UTIL_H__
#घोषणा __CVMX_HELPER_UTIL_H__

/**
 * Convert a पूर्णांकerface mode पूर्णांकo a human पढ़ोable string
 *
 * @mode:   Mode to convert
 *
 * Returns String
 */
बाह्य स्थिर अक्षर
    *cvmx_helper_पूर्णांकerface_mode_to_string(cvmx_helper_पूर्णांकerface_mode_t mode);

/**
 * Setup Ranकरोm Early Drop to स्वतःmatically begin dropping packets.
 *
 * @pass_thresh:
 *		 Packets will begin slowly dropping when there are less than
 *		 this many packet buffers मुक्त in FPA 0.
 * @drop_thresh:
 *		 All incoming packets will be dropped when there are less
 *		 than this many मुक्त packet buffers in FPA 0.
 * Returns Zero on success. Negative on failure
 */
बाह्य पूर्णांक cvmx_helper_setup_red(पूर्णांक pass_thresh, पूर्णांक drop_thresh);

/**
 * Get the version of the CVMX libraries.
 *
 * Returns Version string. Note this buffer is allocated अटलally
 *	   and will be shared by all callers.
 */
बाह्य स्थिर अक्षर *cvmx_helper_get_version(व्योम);

/**
 * Setup the common GMX settings that determine the number of
 * ports. These setting apply to almost all configurations of all
 * chips.
 *
 * @पूर्णांकerface: Interface to configure
 * @num_ports: Number of ports on the पूर्णांकerface
 *
 * Returns Zero on success, negative on failure
 */
बाह्य पूर्णांक __cvmx_helper_setup_gmx(पूर्णांक पूर्णांकerface, पूर्णांक num_ports);

/**
 * Returns the IPD/PKO port number क्रम a port on the given
 * पूर्णांकerface.
 *
 * @पूर्णांकerface: Interface to use
 * @port:      Port on the पूर्णांकerface
 *
 * Returns IPD/PKO port number
 */
बाह्य पूर्णांक cvmx_helper_get_ipd_port(पूर्णांक पूर्णांकerface, पूर्णांक port);

/**
 * Returns the IPD/PKO port number क्रम the first port on the given
 * पूर्णांकerface.
 *
 * @पूर्णांकerface: Interface to use
 *
 * Returns IPD/PKO port number
 */
अटल अंतरभूत पूर्णांक cvmx_helper_get_first_ipd_port(पूर्णांक पूर्णांकerface)
अणु
	वापस cvmx_helper_get_ipd_port(पूर्णांकerface, 0);
पूर्ण

/**
 * Returns the IPD/PKO port number क्रम the last port on the given
 * पूर्णांकerface.
 *
 * @पूर्णांकerface: Interface to use
 *
 * Returns IPD/PKO port number
 */
अटल अंतरभूत पूर्णांक cvmx_helper_get_last_ipd_port(पूर्णांक पूर्णांकerface)
अणु
	बाह्य पूर्णांक cvmx_helper_ports_on_पूर्णांकerface(पूर्णांक पूर्णांकerface);

	वापस cvmx_helper_get_first_ipd_port(पूर्णांकerface) +
	       cvmx_helper_ports_on_पूर्णांकerface(पूर्णांकerface) - 1;
पूर्ण

/**
 * Free the packet buffers contained in a work queue entry.
 * The work queue entry is not मुक्तd.
 *
 * @work:   Work queue entry with packet to मुक्त
 */
अटल अंतरभूत व्योम cvmx_helper_मुक्त_packet_data(काष्ठा cvmx_wqe *work)
अणु
	uपूर्णांक64_t number_buffers;
	जोड़ cvmx_buf_ptr buffer_ptr;
	जोड़ cvmx_buf_ptr next_buffer_ptr;
	uपूर्णांक64_t start_of_buffer;

	number_buffers = work->word2.s.bufs;
	अगर (number_buffers == 0)
		वापस;
	buffer_ptr = work->packet_ptr;

	/*
	 * Since the number of buffers is not zero, we know this is
	 * not a dynamic लघु packet. We need to check अगर it is a
	 * packet received with IPD_CTL_STATUS[NO_WPTR]. If this is
	 * true, we need to मुक्त all buffers except क्रम the first
	 * one. The caller करोesn't expect their WQE poपूर्णांकer to be
	 * मुक्तd
	 */
	start_of_buffer = ((buffer_ptr.s.addr >> 7) - buffer_ptr.s.back) << 7;
	अगर (cvmx_ptr_to_phys(work) == start_of_buffer) अणु
		next_buffer_ptr =
		    *(जोड़ cvmx_buf_ptr *) cvmx_phys_to_ptr(buffer_ptr.s.addr - 8);
		buffer_ptr = next_buffer_ptr;
		number_buffers--;
	पूर्ण

	जबतक (number_buffers--) अणु
		/*
		 * Remember the back poपूर्णांकer is in cache lines, not
		 * 64bit words
		 */
		start_of_buffer =
		    ((buffer_ptr.s.addr >> 7) - buffer_ptr.s.back) << 7;
		/*
		 * Read poपूर्णांकer to next buffer beक्रमe we मुक्त the
		 * current buffer.
		 */
		next_buffer_ptr =
		    *(जोड़ cvmx_buf_ptr *) cvmx_phys_to_ptr(buffer_ptr.s.addr - 8);
		cvmx_fpa_मुक्त(cvmx_phys_to_ptr(start_of_buffer),
			      buffer_ptr.s.pool, 0);
		buffer_ptr = next_buffer_ptr;
	पूर्ण
पूर्ण

/**
 * Returns the पूर्णांकerface number क्रम an IPD/PKO port number.
 *
 * @ipd_port: IPD/PKO port number
 *
 * Returns Interface number
 */
बाह्य पूर्णांक cvmx_helper_get_पूर्णांकerface_num(पूर्णांक ipd_port);

/**
 * Returns the पूर्णांकerface index number क्रम an IPD/PKO port
 * number.
 *
 * @ipd_port: IPD/PKO port number
 *
 * Returns Interface index number
 */
बाह्य पूर्णांक cvmx_helper_get_पूर्णांकerface_index_num(पूर्णांक ipd_port);

#पूर्ण_अगर /* __CVMX_HELPER_H__ */
