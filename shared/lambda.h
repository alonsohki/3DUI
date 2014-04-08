//
// Copyright (c) 2012, Alberto Alonso
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//  * Redistributions in binary form DON'T have to reproduce the above copyright
//    notice, this list of conditions or the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef LAMBDA_H
#define LAMBDA_H

#include <cassert>
#include <cstdlib>
#include <new>

template<typename signature>
class Lambda;

template<typename Ret, typename... Args>
class Lambda<Ret (Args...)>
{
    //------------------------------------------------------------------------------
    // Construction / Destruction
public:
    Lambda ()
    : mData(nullptr)
    {
        clear ();
    }

    Lambda ( const Lambda& other )
    : mData(nullptr)
    {
        if ( other.mData != nullptr )
        {
            // Use the other container's clone method to clone it,
            // and then borrow the functions to work with the
            // lambda buffer.
            mData = other.mClone ( other.mData );
            mClone = other.mClone;
            mDelete = other.mDelete;
            mExecute = other.mExecute;
        }
    }

    template <typename T>
    Lambda ( T const& lambda )
    : mData(nullptr)
    {
        copy ( lambda );
    }
    
    ~Lambda ()
    {
        clear ();
    }

    Lambda& operator= ( const Lambda& other )
    {
        if ( this != &other )
        {
            clear ();

            // Copy the other lambda, same as in the copy constructor.
            if ( other.mData != nullptr )
            {
                mData = other.mClone ( other.mData );
                mClone = other.mClone;
                mDelete = other.mDelete;
                mExecute = other.mExecute;
            }
        }
        return *this;
    }

    // Process nullptr assignments
    Lambda& operator= ( decltype(nullptr) )
    {
        clear ();
        return *this;
    }

    // Copy an actual lambda.
    template <typename T>
    Lambda& operator= ( T const& lambda )
    {
        clear ();
        copy(lambda);
        return *this;
    }

    
    //------------------------------------------------------------------------------
    // Interface functions

    // Ability to use this container as a boolean value to check if
    // we got any lambda stored in.
    operator bool() const
    {
        return mExecute != nullptr;
    }


    // To compare two lambdas, it's enough to just compare the address that they are calling
    // because we can only have two equal lambdas if the Lambda container was assigned from
    // each other.
    bool operator== ( const Lambda& other ) const
    {
        return mExecute == other.mExecute;
    }
    bool operator!= ( const Lambda& other ) const
    {
        return mExecute != other.mExecute;
    }
    bool operator< ( const Lambda& other ) const
    {
        return mExecute < other.mExecute;
    }
    bool operator> ( const Lambda& other ) const
    {
        return mExecute > other.mExecute;
    }

    void clear ()
    {
        if ( mData != nullptr )
        {
            mDelete(mData);
        }
        mDelete = nullptr;
        mExecute = nullptr;
        mClone = nullptr;
        mData = nullptr;
    }


    //------------------------------------------------------------------------------
    // Executor
public:
    Ret operator() ( Args... args ) const
    {
        assert ( mExecute != nullptr );
        return mExecute ( mData, args... );
    }


    //------------------------------------------------------------------------------
    // Method to copy a lambda.
    // Allocate our own memory using malloc, to then perform a placement new on that
    // buffer using the C++11 lambda copy constructor.
private:
    template <typename T>
    void copy ( T const& lambda )
    {
        mData = malloc(sizeof(T));
        new(mData) T ( lambda );
        createDelete<T>();
        createExecute<T>();
        createClone<T>();
    }
    
    //------------------------------------------------------------------------------
    // Methods to create the internal utility functions.
    // We need these to be split from copy() because of some compiler bug
    // that is reusing the function pointer of mDelete for mExecute when
    // the lambda type is "void ()". Apparently, for this compiler, having two
    // lambdas with the same prototype means that they are, clearly, the same lambda.
    template <class T>
    void createDelete ()
    {
        mDelete = [] ( void* data )
        {
            ((T*)data)->~T();
            free(data);
        };
    }
    template <class T>
    void createExecute ()
    {
        mExecute = [] ( void* data, Args... args ) -> Ret
        {
            return ((T*)data)->operator()(args...);
        };
    }
    template <class T>
    void createClone ()
    {
        mClone = [] ( void* data ) -> void*
        {
            void* n = malloc(sizeof(T));
            new(n) T (*(T*)data);
            return n;
        };
    }

    //------------------------------------------------------------------------------
    // Private attributes
private:
    // Lambda data
    void*   mData;

    // Functions to delete, execute and clone our lambda.
    // Should be lambdas that capture nothing, so we can
    // keep a pointer to them even if they get out of scope.
    void    (*mDelete)(void *);
    Ret     (*mExecute)(void *, Args...);
    void*   (*mClone)(void *);
};

#endif

