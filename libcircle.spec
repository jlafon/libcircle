Name:    libcircle
Version: 0.1
Release: 1

Source: %{name}-%{version}-%{release}.tgz                                       
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}                            
URL: http://github.com/hpc/libcircle
Summary: A library used to distribute workloads.
Group: Development/Libraries
License: Copyright (c) 2007-2011 Los Alamos National Security, LLC. All rights reserved.

%description
A simple interface for processing workloads using an automatically distributed global queue.

BuildRequires: openmpi

# Don't strip binaries                                                             
%define __os_install_post /usr/lib/rpm/brp-compress                                
%define debug_package %{nil} 

###############################################################################

%prep                                                                              
%setup -n %{name}-%{version}-%{release}                                            
                                                                                   
%build                                                                             
%configure --program-prefix=%{?_program_prefix:%{_program_prefix}}

make %{?_smp_mflags}                                                               

%install
rm -rf "$RPM_BUILD_ROOT"                                                        
mkdir -p "$RPM_BUILD_ROOT"                                                      
DESTDIR="$RPM_BUILD_ROOT" make install                                          

###############################################################################

%clean                                                                          
rm -rf $RPM_BUILD_ROOT

###############################################################################

%files
%defattr(-,root,root,0755)
%{_prefix}/include/libcircle.h
%{_libdir}/libcircle.so*
%{_libdir}/pkgconfig/libcircle.pc
%{_libdir}/libcircle.a
%{_libdir}/libcircle.la
