/**\file line.hpp
 * \brief Line class
 * 
 * This header contains the Line class, used for building log messages.
 */

#pragma once

#include <string>
#include <memory>
#include <sstream>

#include "level.hpp"
#include "logger_export.hpp"

namespace logger
{
    /**
     * \brief Allows piping content in order to build a log message. Once the object is destroyed, the piped content will be logged to the appropriate outputs.
     */
    class Line
    {
    public:
        // public interface

        /**
         * \brief Logs all contents previously piped into the object to the outputs.
         */
        LOGGER_EXPORT ~Line();

        /**
         * \brief Add content to the log message.
         * \tparam T Any type accepted by a std::ostream.
         * \param value The content to add to the message.
         * \return A reference to this Line object, allowing for continuous piping.
         */
        template<class T>
        Line & operator <<(T value)
        {
            *m_stream << value;
            return *this;
        }

        // internal interface

        /// @private
        Line(const Level & level, std::string context);
        /// @private
        const Level & level() const;
        /// @private
        static std::string currentTimeString(const std::string & format);
        /// @private
        std::string string() const;

        // explicit defaults as requested by clang-tidy (cppcoreguidelines-special-member-functions)

        /// @private
        Line(const Line & line) = default;
        /// @private
        Line(Line&& line) = default;
        /// @private
        Line & operator=(const Line & line) = default;
        /// @private
        Line & operator=(Line && line) = default;

    private:
        Level m_level;
        std::string m_context;
        std::shared_ptr<std::ostringstream> m_stream;
    };
}
